# Philosopher - 42 Project

## Introduction

The Philosophers project is an implementation of the famous dining philosophers problem, a fundamental exercise in concurrency. The goal is to manage multiple threads (or processes) sharing resources (forks) without falling into race conditions or deadlocks.
This project tests your ability to work with multithreading, synchronization with mutexes, and precise timing, while ensuring data integrity in high-concurrency situations.
![Philosopher Table](image/philo_table.gif)

__Project Objectives__
Simulate the behavior of multiple philosophers who think, eat, and sleep.
Ensure synchronization when sharing resources (the forks).
Prevent race conditions and deadlocks.
Implement a control system to detect if a philosopher dies from starvation.

## Key Features
Creation of multiple threads for each philosopher.

Synchronization using mutexes for the forks.

Precise timing control using gettimeofday and usleep.

Detection of philosopher death if they exceed the time_to_die without eating.

Optional control over the number of times each philosopher must eat.

Synchronized messages to display the philosopher's activity (thinking, eating, sleeping, dead).

## Technologies and Concepts Used
C Language

Pthreads and synchronization with pthread_mutex_t

Timing with gettimeofday and usleep

Data structures to manage states and times

Safe and efficient concurrency management

Error handling and resource cleanup

## Common Problems and Solutions
__Deadlock:__

Problem: A deadlock occurs when philosophers are waiting indefinitely for forks. This can happen if all philosophers pick up one fork simultaneously and wait for the second fork, causing a cycle of waiting.

Solution: The most common solution is to implement a strategy like odd/even philosopher rules, where odd-numbered philosophers pick up the left fork first, and even-numbered philosophers pick up the right fork first. This prevents a circular wait and ensures that not all philosophers will hold one fork and wait for another.

__Race Conditions:__

Problem: A race condition can happen when multiple threads try to access shared resources (such as the forks) without proper synchronization, leading to unexpected behaviors.

Solution: Using mutexes (pthread_mutex_t) to lock the forks while a philosopher is eating ensures that only one philosopher can use a fork at a time, preventing race conditions.

__Starvation:__

Problem: Starvation happens when a philosopher never gets the opportunity to eat because the other philosophers keep taking the forks. This could lead to a philosopher "dying" from hunger.

Solution: To avoid starvation, you can implement a mechanism to check the time a philosopher has been waiting to eat. If a philosopher exceeds the time_to_die without eating, they are considered to have "died." Additionally, you can ensure that philosophers are periodically forced to sleep, giving others the opportunity to eat.

## Conclusion
The Philosophers project provides a deep dive into multithreading, synchronization, and concurrency management. It challenges you to think critically about how threads interact with shared resources and how to prevent common concurrency issues like deadlocks and race conditions. By completing this project, you’ll improve your ability to manage concurrency in real-world applications, preparing you for more advanced system-level programming tasks.

