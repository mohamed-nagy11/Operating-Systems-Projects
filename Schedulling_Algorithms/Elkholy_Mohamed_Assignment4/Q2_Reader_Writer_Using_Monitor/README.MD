# Readers/Writers Problem Using Monitors

This program simulates the Readers-Writers problem using monitors and pthreads in C.

## Description

In the Readers-Writers problem, the following conditions are enforced:
1. Any number of readers may simultaneously read the file.
2. Only one writer at a time may write to the file.
3. If a writer is writing to the file, no reader may read.
4. As long as there are readers, a writer should wait.
5. As long as one writer is accessing the shared file, no other writer or reader may access it.
6. If a writer is writing and there exist multiple readers and writers waiting, priority is given to readers.

## Monitor Implementation

The program uses a monitor to implement the solution, with the following procedures and condition variables:

- **Monitor**: `reader_writer`
- **Condition Variables**: `canRead`, `canWrite`
- **Procedures**:
  - `startread()`
  - `endread()`
  - `startwrite()`
  - `endwrite()`

## Compilation

To compile the program, use the provided Makefile. Open a terminal and navigate to the directory containing the source code and Makefile. Run the following command: `make`

This will compile the program, and you can run the executable as follows: `./reader_writer <arguments>`

## Usage

The command-line arguments, which should be either 0 or 1, determine whether the thread is a reader (0) or writer (1). For example:
`./reader_writer 1 0 0 1 0 1 1 0 1 0`

## Clean Up

To remove the compiled files, run: `make clean`
