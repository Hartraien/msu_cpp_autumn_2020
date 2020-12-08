#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <stdexcept>
#include <functional>

const auto MAX_THREADS = std::thread::hardware_concurrency();

class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();

    size_t poolSize();

    // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;

private:
    void inf_loop();

    ThreadPool(const ThreadPool &other) = delete;
    void operator=(const ThreadPool &other) = delete;

private:
    std::vector<std::thread> thread_container;
    std::condition_variable notifier;
    std::queue<std::packaged_task<void()>> TaskQueue;
    std::mutex mutex;
    std::atomic<bool> destr_state = false;
};
#endif // __THREADPOOL_H__

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