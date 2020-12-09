#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <stdexcept>
#include <functional>

namespace tpns
{
    const auto MAX_THREADS = std::thread::hardware_concurrency();

    class ThreadPool
    {
    public:
        //Constructor
        //Argument - number of threads
        explicit ThreadPool(size_t poolSize);
        //Destructor
        //Waits for all Threads to finish
        ~ThreadPool();

        //return number of threads in pool
        size_t poolSize();

        //Execute function func with arguments args
        //Returms std::future that will contain result of function
        template <class Func, class... Args>
        auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;

    private:
        // Method that threads perform
        // Constantly loops over queue
        // (Or waits while it is empty)
        // And executes functions with arguments
        void inf_loop();

        //Pool should not be copyable
        ThreadPool(const ThreadPool &other) = delete;
        void operator=(const ThreadPool &other) = delete;

    private:
        //Contains threads
        std::vector<std::thread> thread_container;
        //Common notifier
        std::condition_variable notifier;
        //List of functions (packaged with arguments) to call
        std::queue<std::packaged_task<void()>> TaskQueue;
        std::mutex mutex;
        std::atomic<bool> destr_state = false;
    };

    template <class Func, class... Args>
    auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        using return_type = decltype(func(args...));
        std::packaged_task<return_type()> task(std::bind(func, args...));
        std::future<return_type> task_res = task.get_future();
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            this->TaskQueue.emplace(std::packaged_task<void()>(std::move(task)));
        }
        this->notifier.notify_one();
        return task_res;
    }
} // namespace tpns
#endif // __THREADPOOL_H__