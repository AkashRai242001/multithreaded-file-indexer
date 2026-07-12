#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

int counter = 0;
std::mutex counter_mutex;

void worker(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(counter_mutex);
        counter++;
        std::cout << "Thread " << id << " incremented counter to " << counter << "\n";
        lock.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.push_back(std::thread(worker, i));
    }
    for (auto& t : threads) {
        t.join();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Final counter: " << counter << "\n";
    std::cout << "Time: " << duration.count() << " ms\n";
    return 0;
}