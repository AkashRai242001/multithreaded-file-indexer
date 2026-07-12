#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1;
std::mutex m2;

void thread_A() {
    std::cout << "Thread A: Trying to lock m1...\n";
    m1.lock();
    std::cout << "Thread A: Locked m1!\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Give B time to lock m2
    
    std::cout << "Thread A: Trying to lock m2...\n";
    m2.lock();  // Will BLOCK here!
    std::cout << "Thread A: Locked m2!\n";  // Never reached
    
    m2.unlock();
    m1.unlock();
}

void thread_B() {
    std::cout << "Thread B: Trying to lock m2...\n";
    m2.lock();
    std::cout << "Thread B: Locked m2!\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Give A time to lock m1
    
    std::cout << "Thread B: Trying to lock m1...\n";
    m1.lock();  // Will BLOCK here!
    std::cout << "Thread B: Locked m1!\n";  // Never reached
    
    m1.unlock();
    m2.unlock();
}

int main() {
    std::cout << "Starting deadlock demo. Press Ctrl+C if it hangs (it will).\n\n";
    
    std::thread t1(thread_A);
    std::thread t2(thread_B);
    
    t1.join();  // Will hang here forever
    t2.join();
    
    std::cout << "This line never prints.\n";
    return 0;
}