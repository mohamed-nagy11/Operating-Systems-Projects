# FCFS Reader/Writer Programming

This program simulates the Readers-Writers problem using semaphores and multi-threading in C.

## Description:

The program demonstrates a solution to the Readers-Writers problem. Multiple reader threads can access the data simultaneously for reading, while writer threads have exclusive access for writing. The reading and writing processes are simulated by sleeping for 1 second.

## Implementation Details:

1. The reader function simulates the behavior of a reader thread. It accesses the shared resource for reading and then releases the resource.

2. The writer function simulates the behavior of a writer thread. It acquires exclusive access to the shared resource for writing and then releases it.

3. Semaphores mutex, writeBlock, and readBlock are used for thread synchronization to manage critical sections.

## Compilation:

Run the makefile using the command `make`.

## Usage:

The program takes command-line arguments to determine the type of thread to create. The command-line arguments, which should be either 0 or 1, determine whether the thread is a reader (0) or writer (1). For example, ./sem_exe 1 0 0 1 0 1 1 0 1 0

## Acknowledgment:

- This assignment was done in pair with `Ibrahim Elseidi`.
