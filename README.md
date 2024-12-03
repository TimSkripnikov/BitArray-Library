# BitArray Library

The **BitArray** library is a C++ implementation of a dynamic array of bits, providing various bitwise operations, resizing, and other utilities for managing and manipulating bits efficiently.

This project was created as an assignment for the university course ‘Object-Oriented Programming in C++’.


## Building and Running

To build and execute the project, follow these steps:

1. **Clone the repository** (if not already done):
   ```bash
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Generate build files**:
   ```bash
   cmake -S . -B build
   ```

3. **Build the project**:
   ```bash
   cmake --build build
   ```

4. **Run the tests**:
   ```bash
   ./build/tests/BitArrayTest
   ```



## Running Tests

The project includes unit tests to verify the functionality of the `BitArray` class. The tests are compiled and executed as part of the build process using the command in step 4 above. Upon execution, you will see the results of the test cases in the terminal.

---
