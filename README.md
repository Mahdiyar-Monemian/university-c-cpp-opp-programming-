# University C/C++ Object-Oriented Programming Projects

A collection of advanced C++ projects developed during university, focusing on robust object-oriented programming (OOP) principles, memory management, and clean, orthodox C++ design. These projects demonstrate a strong foundation in systems programming and software engineering best practices.

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OOP](https://img.shields.io/badge/Object%20Oriented-Programming-ff69b4)

## 📁 Projects Overview

This repository contains three distinct console-based applications, each tackling a unique problem with a specific architectural focus:

### 1. 🍽️ Restaurant In-Terminal System
A complete simulation of a restaurant management system, handling orders, menus, tables, and billing.
-   **Key Feature: Purity of Design**
    -   **Zero Global Variables:** This project was architected with meticulous attention to scope and encapsulation. The entire application state is managed through well-defined class interfaces and local variables, eliminating side effects and promoting testability and maintainability.
-   **Concepts Demonstrated:** Class Composition, Operator Overloading, Stream I/O, Menu-Driven Interfaces.

### 2. 🧮 Big Number Arithmetic Library
A custom C++ library that enables arithmetic operations on integers of arbitrary size, exceeding the limits of native C++ data types.
-   **Key Feature: Orthodox C++ & Clean Code**
    -   This project represents some of **the most clean and orthodox C++ code you can get.** It adheres strictly to fundamental OOP principles and C++ best practices:
        -   **Resource Management:** Proper implementation of the Rule of Three/Five (Destructor, Copy Constructor, Copy Assignment Operator).
        -   **Minimalistic Design:** No unnecessary dependencies; pure, standard C++.
        -   **Clear Abstraction:** A simple and intuitive interface for complex underlying operations.
-   **Concepts Demonstrated:** Dynamic Memory Management, Operator Overloading (`, `, `*`, `==`, `<<`), Low-Level Algorithm Design.

### 3. 🛒 Supermarket In-Terminal System
A comprehensive supermarket inventory and point-of-sale (POS) system simulating product management, shopping carts, and transactions.
-   **Key Feature: Elegant Persistent Storage System**
    -   The save/load system is a masterclass in leveraging C++ features for simplicity and power.
    -   **Polymorphic I/O:** Each class in the hierarchy (e.g., `Product`, `Cart`, `User`) implements its own `operator<<` (output) and `operator>>` (input) for serialization.
    -   **Effortless Data Management:** Saving the entire state of the supermarket to a file is as simple as calling `file << object;`. Loading is equally straightforward, using these overloaded operators to reconstruct the object hierarchy from disk seamlessly. This design is both powerful and exceptionally clean.
-   **Concepts Demonstrated:** Polymorphism, Inheritance, File I/O, Advanced Operator Overloading, Serialization.

## 🛠️ Tech Stack

-   **Language:** C++ (Standard 11/14)
-   **Paradigm:** Object-Oriented Programming (OOP)
-   **Platform:** Platform-independent (Standard Library only)
-   **Interface:** Console/Terminal

## 📦 Compilation and Running

### Prerequisites
-   A C++ compiler supporting C++11 or newer (e.g., `g++`, `clang++`, MSVC).

### Compile and Run Any Project
Each project is contained in its own directory with a main source file.

1.  **Navigate to a project directory:**
    ```bash
    cd "Resturant in-terminal"
    ```

2.  **Compile the source code:**
    ```bash
    g++ -std=c++11 -o program *.cpp
    ```

3.  **Run the executable:**
    ```bash
    ./program
    ```

## 🧠 Academic Focus

These projects were designed to rigorously practice and demonstrate core computer science concepts:
-   **Object-Oriented Design:** Deep use of encapsulation, inheritance, and polymorphism.
-   **Memory Management:** Manual control of dynamic memory in the Big Number project.
-   **C++ Idioms:** Mastery of operator overloading, stream interfaces, and the Rule of Three.
-   **Data Structures:** Implementation of custom data structures for specific computational needs.
-   **Software Architecture:** Designing systems with maintainability, scalability, and clarity in mind.

## 📝 Note

These are academic projects from my university coursework. They are console-based and focus on core logic and architecture rather than graphical user interfaces.

---

**This repository serves as a testament to a strong foundational understanding of C++ and object-oriented programming principles.**
