# Learning Journey: C++ Multithreading Mastery

This document tracks my progression through concurrent programming concepts.

## Lesson 1: Thread Fundamentals

**Concepts learned:**
- `std::thread` creation and lifecycle
- Thread joining vs detaching
- Nondeterministic execution
- Parallel vs concurrent execution

**Key experiment:** Created 4 worker threads + main, observed ~320ms parallel 
execution (vs 900ms sequential). Confirmed nondeterministic output ordering.

**Deliverable:** [examples/01_basic_threads.cpp](../examples/01_basic_threads.cpp)

---

## Lesson 2: Race Conditions & Mutexes

**Concepts learned:**
- What a race condition is (non-atomic operations)
- CPU instruction-level view of `counter++` (load-modify-store)
- `std::mutex` for mutual exclusion
- RAII pattern with `std::lock_guard`
- Lock granularity trade-offs (fine vs coarse)

**Key experiment:** Empirically demonstrated race condition — 8 threads 
incrementing a counter 100,000 times each lost 70-75% of increments without 
protection. Mutex fixed it at 17× performance cost.

**Insight:** Coarse-grained locking (lock outside loop) was 20× faster but 
serialized execution — a classic anti-pattern that defeats parallelism.

**Deliverables:** 
- [examples/02a_race_condition.cpp](../examples/02a_race_condition.cpp)
- [examples/02b_mutex_fix.cpp](../examples/02b_mutex_fix.cpp)
- [examples/02c_lock_guard.cpp](../examples/02c_lock_guard.cpp)

---

## Upcoming Lessons

- **Lesson 3:** `unique_lock`, `scoped_lock`, deadlock prevention
- **Lesson 4:** Condition variables & producer-consumer
- **Lesson 5:** Atomics & memory ordering
- **Lesson 6:** Futures, promises, async
- **Lesson 7:** Thread pool from scratch
- **Lesson 8:** File indexer integration
- **Lesson 9:** Performance optimization