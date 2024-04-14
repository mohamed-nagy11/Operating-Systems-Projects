# shared_memory
shared_memory.c creates shared memory, generates random numbers, and writes them into the shared memory.

## Usage:
1. Run the makeile: make
2. Run the program: ./shared_memory

## Program Steps:
1. Generate 10 random numbers ranging from 1 to 1000.
2. Create a shared memory segment of size 2048 bytes.
3. Write the generated numbers to the shared memory.
4. Detach from the shared memory.



# ascending_sorter
ascending_sorter.c reads numbers from shared memory, sorts them in ascending order, and prints the sorted result.

## Usage:
1. Run the makefile: make
2. Run the program: ./ascending_sort

$## Program Steps:
1. Attach to the existing shared memory segment.
2. Read numbers from shared memory.
3. Sort the numbers in ascending order.
4. Print the sorted numbers.
5. Detach from the shared memory.



# descending_sorter
descending_sorter.c is a C program that reads numbers from shared memory, sorts them in descending order, prints the sorted result, and removes the shared memory.

## Usage:
1. Run the makefile: make
2. Run the program: ./descending_sort

## Program Steps:
1. Attach to the existing shared memory segment.
2. Read numbers from shared memory.
3. Sort the numbers in descending order.
4. Print the sorted numbers.
5. Detach from the shared memory.
6. Remove the shared memory segment.
