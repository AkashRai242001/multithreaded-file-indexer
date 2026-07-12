#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1;
std::mutex m2;

void thread_A() {
    std::cout << "Thread A: Trying to lock BOTH m1 and m2...\n";
    std::scoped_lock lock(m1, m2);  // Locks both mutexes without risk of deadlock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    std::cout << "Thread A: Finished work with m1 and m2.\n";
}

void thread_B() {
    std::cout << "Thread B: Trying to lock BOTH m1 and m2...\n";
    std::scoped_lock lock(m1, m2);  // Locks both mutexes without risk of deadlock
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work
    std::cout << "Thread B: Finished work with m1 and m2.\n";
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(thread_A);
    std::thread t2(thread_B);
    
    t1.join();  // Will hang here forever
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "Execution time: " << duration.count() << " ms\n";
    return 0;
}