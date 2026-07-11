#include<iostream>
#include<thread>
#include<chrono>
#include<vector>

int num_workers = 4;

void worker() {
    std::cout << "worker thread id : " << std::this_thread::get_id() << "\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Worker iteration : " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Worker thread finished.\n";
}

int main() {
    int start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "Main thread id : " << std::this_thread::get_id() << "\n";
    
    for (int i = 0; i < 3; ++i) {
        std::cout << "Main iteration : " << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < num_workers; ++i) {
        threads.push_back(std::thread(worker));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Main thread finished.\n";
    int end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "Execution time : " << ((end - start)) << " milliseconds\n";
    return 0;
}