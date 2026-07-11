# Multithreaded File Indexing Engine

A high-performance, thread-safe file indexing engine built in modern C++ (C++17), 
demonstrating mastery of concurrent programming primitives.

## 🎯 Project Goals

Build a production-grade file indexing engine while mastering:
- `std::thread` and thread lifecycle management
- Mutexes and lock-based synchronization
- RAII patterns with `std::lock_guard` / `std::unique_lock`
- Condition variables for thread coordination
- Atomics and lock-free programming
- Thread pools and task scheduling
- Producer-consumer patterns
- Performance profiling and optimization

## 🏗️ Current Progress

- ✅ **Lesson 1:** Thread basics — creation, joining, parallel execution
- ✅ **Lesson 2:** Race conditions & mutexes — protecting shared state
- 🚧 **Lesson 3:** Advanced locking (`unique_lock`, `scoped_lock`, deadlock prevention)
- 📅 **Lesson 4:** Condition variables (producer-consumer)
- 📅 **Lesson 5:** Atomics and memory ordering
- 📅 **Lesson 6:** Futures and promises
- 📅 **Lesson 7:** Thread pool implementation
- 📅 **Lesson 8:** File indexer integration
- 📅 **Lesson 9:** Performance optimization

## 📊 Key Learnings So Far

### Race Condition Demonstration (Lesson 2)

Ran 8 threads incrementing a shared counter 100,000 times each (expected: 800,000):

| Version | Counter Value | Correctness | Time |
|---------|--------------|-------------|------|
| Unprotected | 198,845 – 238,833 | ❌ 25-30% correct | 3-4 ms |
| `std::mutex` | 800,000 | ✅ 100% | 51-70 ms |
| `std::lock_guard` | 800,000 | ✅ 100% | 60-68 ms |

**Insight:** Race conditions caused ~70% of increments to be lost. Mutex protection 
restored correctness at ~17× performance cost — an acceptable trade-off for correctness.

## 🛠️ Build & Run

### Prerequisites
- C++17 compiler (g++, clang++, or MSVC)
- (Optional) CMake 3.15+

### Compile Examples

```bash
# Lesson 1: Basic threads
g++ -std=c++17 -pthread -o examples/01_basic examples/01_basic_threads.cpp

# Lesson 2c: lock_guard version
g++ -std=c++17 -pthread -o examples/02c_lockguard examples/02c_lock_guard.cpp
```

### Run

```bash
./examples/01_basic
./examples/02c_lockguard
```

## 📁 Repository Structure