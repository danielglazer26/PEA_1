//
// Created by elmod on 22.10.2022.
//

#ifndef ALGORYTMY2_THREADPOOL_H
#define ALGORYTMY2_THREADPOOL_H


#include <mutex>
#include <vector>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include "../../Header/B&B/Node.h"

class ThreadPool {
public:
    void Start();

    void QueueJob(const std::function<void()> &job);

    void Stop();

    bool isEmpty();

    bool checkIfThreadIsWorking();

private:
    void ThreadLoop(int i);

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
    std::vector<bool> threadsIsWorking;
};

#endif //ALGORYTMY2_THREADPOOL_H
