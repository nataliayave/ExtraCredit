In-Memory Database with Transaction Support

Overview

This project implements an in-memory key-value database in C++ that supports basic operations like get, put, and transactional features such as begin_transaction, commit, and rollback. The database ensures data integrity by isolating changes during a transaction until they are committed or discarded.

Features

Transaction Management:

 - Start a transaction using begin_transaction.
 - Commit changes to the main database using commit.
 - Revert changes using rollback.

Key-Value Storage:
 - Store and retrieve data using put and get.
 - Key type: std::string
 - Value type: int

Error Handling:
 - Throws exceptions for invalid operations

Requirements

 - C++17 or higher
 - Standard C++ compiler (e.g., g++, clang)
 - C++ Standard Library

Installation and Compilation

Clone the repository:
 - git clone <repository_url>
 - cd <repository_directory>

Compile the code using a C++ compiler. For example, with g++:
 - g++ -o in_memory_db in_memory_db.cpp
Run the program:
 - ./in_memory_db

Suggested Improvements

If this assignment becomes an official course project, the following improvements can be made:

Clarify Instructions:

 - Specify the expected behavior for nested or overlapping transactions (e.g., should they be allowed?).
 - Provide clear guidelines on handling invalid keys and operations outside a transaction.

Enhance Features:

 - Add support for additional methods like delete(key) and list_keys().
 - Extend functionality to support more data types or complex nested transactions.

Grading Enhancements:

 - Include unit tests to verify correctness automatically.
 - Provide sample input/output scenarios for comprehensive testing.