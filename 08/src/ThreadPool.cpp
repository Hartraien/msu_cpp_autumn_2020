#include "ThreadPool.hpp"

tpns::ThreadPool::ThreadPool(size_t poolSize)
{
    //Checks that poolSize is within bounds
    if (poolSize == 0)
        throw std::invalid_argument("Pool size can't be 0");
    if (poolSize > tpns::MAX_THREADS)
        throw std::invalid_argument("Pool size can't be higher than MAX_THREADS");

    //Create threads that execute threadWorkerMethod method of this class
    this->thread_container.reserve(poolSize);
    for (size_t i = 0; i < poolSize; i++)
    {
        //this is passed so that it will access memebers of this instance
        thread_container.emplace_back(&ThreadPool::threadWorkerMethod, this);
    }
}

tpns::ThreadPool::~ThreadPool()
{
    this->destr_state = true;

    //Awakes all threads
    //So that they may be joined before destruction
    notifier.notify_all();
    for (auto &thread : this->thread_container)
    {
        thread.join();
    }
}

size_t tpns::ThreadPool::poolSize()
{
    return this->thread_container.size();
}

void tpns::ThreadPool::threadWorkerMethod()
{
    //Infinitely loops over task_queue
    //Takes first Func
    //And executes it
    while (true)
    {
        // task to execute (will be used to get task from queue)
        std::packaged_task<void()> task;
        // block to use unique_lock only for getting tasks from queue and unlock after execution
        {
            //locks common mutex, so that queue is not accessed simultaneously
            std::unique_lock<std::mutex> lock(mutex);

            // if queue is empty, stops until notification
            // it unlocks lock while waiting and locks it when notified
            // also unlocks by destructor, so that all thread will be stopped
            notifier.wait(lock, [this] { return (!this->task_queue.empty() || this->destr_state); });

            // if notified by destructor
            if (destr_state)
                break;

            //get_task_from queue
            task = std::move(task_queue.front());
            //remove task from queue
            task_queue.pop();
        }
        //execute_task
        task();
    }
}
