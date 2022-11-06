
#include <iostream>
#include "../../Header/B&B/ThreadPool.h"

void ThreadPool::start(int numberOfThreads) {
    const uint32_t num_threads = 4; // Max # of threads the system supports
    threads.resize(num_threads);
    threadsIsWorking.resize(num_threads);
    for (int i = 0; i < num_threads; i++) {
        threadsIsWorking.at(i) = false;
        threads.at(i) = std::thread(&ThreadPool::mainThreadLoop, this, i);
    }
}

void ThreadPool::mainThreadLoop(int i) {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, [this, i] {
                threadsIsWorking.at(i) = false;
                return !jobs.empty() || should_terminate;
            });
            if (should_terminate) {
                return;
            }
            threadsIsWorking.at(i) = true;
            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}

void ThreadPool::queueJob(const std::function<void()> &job) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

bool ThreadPool::isEmpty() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        poolbusy = jobs.empty();
    }
    return poolbusy;
}

void ThreadPool::Stop() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (std::thread &active_thread: threads) {
        active_thread.join();
    }
    threads.clear();
}

bool ThreadPool::checkIfThreadIsWorking(){
    std::unique_lock<std::mutex> lock(queue_mutex);
    return std::any_of(threadsIsWorking.begin(), threadsIsWorking.end(), [](bool b){return b;});
}

