#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t poolSize)
{
    if (poolSize == 0)
        throw std::invalid_argument("Pool size can't be 0");
    if (poolSize > MAX_THREADS)
        throw std::invalid_argument("Pool size can't be higher than MAX_THREADS");

    this->thread_container.reserve(poolSize);
    for (size_t i = 0; i < poolSize; i++)
    {
        thread_container.emplace_back(&ThreadPool::inf_loop, this);
    }
}

ThreadPool::~ThreadPool()
{
    this->destr_state = true;
    notifier.notify_all();
    for (auto &thread : this->thread_container)
    {
        thread.join();
    }
}

size_t ThreadPool::poolSize()
{
    return this->thread_container.size();
}

void ThreadPool::inf_loop()
{
    //Infinitely loops over TaskQueue
    //Takes first Func
    //And executes it
    while (true)
    {
        std::packaged_task<void()> task;
        // block to use unique_lock only for getting
        {
            std::unique_lock<std::mutex> lock(mutex);

            // if queue is empty, stops until notification
            // it unlocks lock while waiting and locks it when notified
            notifier.wait(lock, [this] { return (!this->TaskQueue.empty() || this->destr_state); });

            // if notified by destructor
            if (destr_state)
                break;

            //get_task_from_queue
            task = std::move(TaskQueue.front());
            TaskQueue.pop();
        }
        //execute_task
        task();
    }
}
