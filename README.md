
# SingleLinkedList Project

A custom implementation of a single-linked list in C++. This project is part of my learning portfolio, showcasing my skills in C++ data structures, memory management, and the Standard Template Library (STL). The SingleLinkedList class provides an efficient, user-defined singly linked list supporting basic operations such as insertion, deletion, and iteration. 

## Features

• **Iterator Support**: Custom iterator implementation with `BasicIterator`, allowing standard forward iteration.  
• **Standard Container Functions**: Includes essential linked list functions like `PushFront`, `InsertAfter`, `PopFront`, and `EraseAfter`.  
• **Operator Overloads**: Supports equality and comparison operators for easy list comparison.  
• **Exception Safety**: Includes exception-safety mechanisms, particularly in `InsertAfter`.  
• **Memory Management**: Efficient dynamic memory handling using RAII principles.  

## Code Structure

The code is divided into the following key components:

• `Node`: Internal struct that represents each element in the list.  
• `BasicIterator`: Custom iterator class for traversing through the linked list.  
• `SingleLinkedList`: Main class implementing the singly linked list with functions for modifying and accessing the list.  

## Installation and Setup

### Prerequisites

• **Compiler**: C++11 or higher compatible compiler (e.g., GCC, Clang, MSVC).  
• **Build System**: CMake 3.10+ recommended for easy project configuration.  

### Step 1: Clone the Repository:

Clone this repository to your local machine:

```bash
git clone git@github.com:Daria-Chepurnaia/cpp-single-linked-list.git
cd cpp-single-linked-list
```
### Step 2: Compile the Project:


```bash
g++ -std=c++17 main.cpp -o SingleLinkedList
```
### Step 3: Run the Project:

```bash
./SingleLinkedList
```

## Code Highlights

• **Insertion and Deletion:** Supports `PushFront`, `PopFront`, `InsertAfter`, and `EraseAfter` operations, with time complexity `O(1)`.  
• **Iterator Implementation:** `BasicIterator` class allows forward traversal of the list.  
• **Operator Overloads:** Includes equality and comparison operators for comparing lists.  

## Usage Example

Here's an example usage:

```cpp
SingleLinkedList<int> list{1, 2, 3};
list.PushFront(0);
for (const auto& item : list) {
    std::cout << item << " ";
}
// Output: 0 1 2 3

```
## Test Coverage

The code is thoroughly covered with unit tests that verify the functionality and integrity of the `SingleLinkedList` class. Each test case ensures that the various operations, including insertion, deletion, and exception handling, work as expected. The tests also check the robustness of the implementation against edge cases, ensuring a reliable and safe use of the data structure.

The main function calls the tests defined in tests.h, executing them when the program runs.


## License

This project is licensed under the [MIT License](https://github.com/Daria-Chepurnaia/cpp-single-linked-list/blob/main/LICENSE.txt).

