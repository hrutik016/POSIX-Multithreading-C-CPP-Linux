# Part A – POSIX Multithreading Fundamentals

This directory contains foundational examples of **POSIX multithreading** using **C/C++ on Linux**. Each subfolder focuses on a core concept, progressing from thread creation to synchronization mechanisms. These examples are ideal for beginners and intermediate learners looking to understand real-time, multi-threaded application development.

---

## 📚 Table of Contents
- [Folder Structure](#-folder-structure)
- [Sample Compilation & Execution](#-sample-compilation--execution)
- [Learning Objectives](#-learning-objectives)

---

## 📁 Folder Structure

| Folder No. | Topic                  | Description |
|------------|------------------------|-------------|
| 1          | Hello World            | Basic thread creation and execution using `pthread_create`. |
| 2          | Joinable Thread        | Demonstrates joinable threads with `pthread_join`. |
| 3          | GLThreads              | Illustrates generalized linked threads and callback structure. |
| 4          | NFC                    | Simulates threading concepts in an NFC-style setup. |
| 5          | Thread Cancel          | Demonstrates how to cancel a thread using `pthread_cancel`. |
| 6          | Event Listeners        | Implements thread-based event handling. |
| 7          | Mutex                  | Basic mutual exclusion using `pthread_mutex`. |
| 8          | Consumer Producer      | A classic producer-consumer implementation using mutex and condition variables. |
| 9          | Dining Philosopher     | The synchronization challenge solved with mutexes. |
| 10         | Thread Barriers        | Synchronizing thread progress using barriers. |
| 11         | Semaphores             | Demonstrates thread control with `sem_t` for limited concurrent access. |
| 12         | Recursive Mutex        | Shows how recursive locks prevent deadlocks in nested lock scenarios. |
| 13         | Read Write Locks       | Performance-optimized locking for read-heavy environments. |
| 14         | CRUD                   | Simulates multi-threaded Create/Read/Update/Delete operations with fine-grained locking. |

---

## 🧪 Sample Compilation & Execution

All examples are written in standard C and can be compiled using `gcc`. For folders containing multiple source files, a `compile.sh` is usually provided.

### ✅ Example: Compile and Run `Hello World`

```bash
gcc hello_world.c -o hello_world -lpthread
./hello_world
```

### ✅ Example: Compile and Run Semaphores

```bash
gcc semaphore.c -o semaphore -lpthread
./semaphore
```

> 🧠 Note: Most programs generate .o and .exe files along with source .c files. Ensure -lpthread is included when compiling, as it's essential for POSIX threads.


## 🎯 Learning Objectives
✅ Learn how to create and manage threads using the POSIX pthread library.

✅ Understand the difference between joinable and detached threads.

✅ Apply mutexes, semaphores, and condition variables for inter-thread synchronization.

✅ Solve classic problems such as Producer-Consumer and Dining Philosophers using threading techniques.

✅ Explore advanced thread coordination tools like recursive mutexes, read-write locks, and barriers.

✅ Build real-world multi-threaded applications like event listeners and CRUD operations.

