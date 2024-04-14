# Process-based FCFS Readers-Writers Solution

This program simulates the Readers-Writers problem using semaphores and processes in C.

## Description

The program provides a solution to the Readers-Writers problem, where multiple reader processes can access shared data simultaneously for reading, while writer processes have exclusive access for writing. The simulated reading and writing processes are simulated by sleeping for 1 second.

## Implementation Details

1. The `child_reader` function simulates the behavior of a reader process. It accesses the shared resource for reading and then releases the resource.

2. The `child_writer` function simulates the behavior of a writer process. It acquires exclusive access to the shared resource for writing and then releases it.

3. Semaphores `mutex`, `writeBlock`, and `readBlock` are used for process synchronization to manage critical sections.

## Compilation

Run the makefile using the command `make`.

## Usage

The program takes command-line arguments to determine the type of process to create. The command-line arguments, which should be either 0 or 1, determine whether the process is a reader (0) or writer (1). For example, `./Extrasem_exe 1 0 0 1 0 1 1 0 1 0`.

## Notes

- The program uses shared memory to store variables and semaphores shared among processes.
- Semaphores and variables are initialized in shared memory.
- Child processes exit with `exit(0)` to signify normal termination, and abnormal terminations are printed by the parent process.

