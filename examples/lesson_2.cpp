#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

int counter = 0;
std::mutex counter_mutex;

void worker(int id, int iterations) {
    std::lock_guard<std::mutex> guard(counter_mutex);
    for (int i = 0; i < iterations; ++i) {
        // counter_mutex.lock();
        counter++;
        // counter_mutex.unlock();
    }
    std::cout << "Thread " << id << " done\n";
}

int main() {
    int num_threads = 8;
    int iterations_per_thread = 100000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(worker, i, iterations_per_thread));
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Counter value: " << counter << " (expected: " 
              << (num_threads * iterations_per_thread) << ")\n";
    std::cout << "Lost increments: " 
              << ((num_threads * iterations_per_thread) - counter) << "\n";
    std::cout << "Time: " << duration.count() << " ms\n";
    
    return 0;
}