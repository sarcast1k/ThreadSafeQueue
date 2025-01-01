# ThreadSafeQueue
A simple and efficient C++ thread-safe queue implementation using `std::mutex` and `std::condition_variable`. This library provides a way to enqueue and dequeue items in a thread-safe manner, making it suitable for use in multithreaded applications.

## Features

- **Thread Safety**: Implements a thread-safe queue using `std::mutex` and `std::condition_variable` to ensure safe operations in multithreaded environments.
- **Basic Operations**: Provides `enqueue` and `dequeue` methods to safely add and remove items from the queue.
- **Flexible and Lightweight**: Easy to integrate and use, with no external dependencies.
- **Producer-Consumer Model**: Supports use cases where multiple threads need to produce and consume items concurrently.
- **Performance**: Suitable for both high-performance scenarios and simple use cases.

## Installation

There are two ways to use the `ThreadSafeQueueLibrary` in your project: by **directly including** the header file or by **building the library** and linking it with your project.

### 1. **Using the Library Directly**

If you want to quickly integrate the `ThreadSafeQueue` into your project, you can simply include the header file `ThreadSafeQueue.h`:

1. Download or clone this repository.
2. Copy the `ThreadSafeQueue.h` file into your project.
3. Include the header file in your code:

    ```cpp
    #include "ThreadSafeQueue.h"
    ```

Now you can use the `ThreadSafeQueue` class in your project.

### 2. **Building the Library Using CMake**

You can also build this library as a static or shared library and link it to your project. This is useful if you want to reuse the library in multiple projects without copying the header file directly.

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/sarcast1k/ThreadSafeQueue
    ```

2. Create a build directory and configure the project with CMake:

    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3. Build the library:

    ```bash
    cmake --build .
    ```

    This will generate the `ThreadSafeQueue` library (static or shared depending on your configuration).

4. Link your project with the `ThreadSafeQueue` library. You can do this by specifying the path to the compiled library in your build system (for example, in your `CMakeLists.txt` if you're using CMake).

    Example of linking with CMake:

    ```cmake
    add_executable(your_project main.cpp)
    target_link_libraries(your_project ThreadSafeQueue)
    ```

### 3. **Using the Library in Your Project**

Once the library is integrated or built, you can use it like so:

```cpp
#include "ThreadSafeQueue.h"

ThreadSafeQueue<int> queue;

// Producer thread function
void producer(ThreadSafeQueue<int>& q) {
    for (int i = 0; i < 10; ++i) {
        q.enqueue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    }
}

// Consumer thread function
void consumer(ThreadSafeQueue<int>& q) {
    int item;
    for (int i = 0; i < 10; ++i) {
        if (q.dequeue(item)) {
            std::cout << "Consumed: " << item << std::endl;
        }
    }
}

int main() {
    ThreadSafeQueue<int> queue;

    std::thread producer_thread(producer, std::ref(queue));
    std::thread consumer_thread(consumer, std::ref(queue));

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
