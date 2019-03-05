# Deque
Data structure 2018 course work

deque is an irregular acronym of double-ended queue. Double-ended queues are sequence containers with dynamic sizes that can be expanded or contracted on both ends (either its front or its back).

## Requirements
* the same operations with Deque in C++ STL
* use iterator
* no memory leaking
* need to optimize time complexity for test

## Realization
use blocks
* the block is a dynamic array and all pointers to blocks are stored in a dynamic array(finished)
  * it's right but time-consuming.
  * Time Limit Exceed
* the block is a linked list and a big linked list is consist of all the blocks(finished)
  * it's right and fast.

