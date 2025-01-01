// include/ThreadSafeQueue.h
// GNU GPL3 license under sarcast1k@github.com

// 
// ThreadSafeQueue library file
//

#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> data_queue;
    std::mutex queue_mutex;
    std::condition_variable data_available;

public:
    // enqueue an item to the queue thread-safely
    void enqueue(const T& item) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        data_queue.push(item);
        data_available.notify_one();
    }

    // dequeue an item from the queue thread-safely
    bool dequeue(T& item) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        // wait until an item is available
        data_available.wait(lock, [this] { return !data_queue.empty(); });
        if (!data_queue.empty()) {
            item = data_queue.front();
            data_queue.pop();
            return true;
        }
        return false;
    }

    // check if the queue is empty thread-safely
    bool empty() const {
        std::lock_guard<std::mutex> lock(queue_mutex);
        return data_queue.empty();
    }

    // get the size of the queue thread-safely
    size_t size() const {
        std::lock_guard<std::mutex> lock(queue_mutex);
        return data_queue.size();
    }
};

#endif
