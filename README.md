AI Smart City Navigator
AI Smart City Navigator is an algorithm-driven navigation system designed to simulate real-world smart city routing using Artificial Intelligence techniques and Data Structures & Algorithms.

The project focuses on efficient shortest path computation, traffic-aware routing, and clean software architecture using modern C++ and Object-Oriented Programming.

-- Algorithms Used
Dijkstra’s Algorithm
Computes the shortest distance between two locations
A (A-Star) Algorithm*
Improves performance using heuristics

Considers:
Node-based (location) heuristics
Edge-based (road & traffic) heuristics
This makes navigation faster, smarter, and closer to real-world systems.

-- Architecture Overview
The system follows a component-based and modular architecture:
Graph Module – Manages nodes, edges, and routing algorithms
Admin Module – Adds/removes locations and roads
User Module – Queries shortest and smart paths
Storage Module – Handles file-based persistent storage
Main Controller – Integrates all components

Each module is implemented in separate source files for better maintainability and scalability.

-- Data Persistence
Binary file handling (no external database)
Saves and loads:
City locations
Roads and traffic data
Fast, lightweight, and platform-independent

-- Technologies & Concepts

C++
Object-Oriented Programming (OOP)
Graphs & Adjacency Lists
Priority Queues
Dijkstra & A* Algorithms
AI Heuristics
File Handling (Binary I/O)
Modular Software Design

-- Learning Outcomes
Practical implementation of graph algorithms
Understanding of AI-based heuristics
Real-world problem-solving approach
Experience with scalable and maintainable code design
