// src/testing.cpp
// GNU GPL3 license under sarcast1k@github.com

// 
// ThreadSafeQueue test file
//

#include <iostream>
#include <thread>
#include <chrono>
#include "ThreadSafeQueue.h"

// producer function
void producer(ThreadSafeQueue<int>& tsq) {
    for (int i = 0; i < 10; ++i) {
        tsq.enqueue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    }
}

// consumer function
void consumer(ThreadSafeQueue<int>& tsq) {
    int item;
    for (int i = 0; i < 10; ++i) {
        if (tsq.dequeue(item)) {
            std::cout << "Consumed: " << item << std::endl;
        }
    }
}

int main() {
    ThreadSafeQueue<int> tsq;  // create a thread-safe queue of integers

    // create producer and consumer threads
    std::thread prod(producer, std::ref(tsq));
    std::thread cons(consumer, std::ref(tsq));

    // wait for both threads to finish
    prod.join();
    cons.join();

    return 0;
}
