# 🎓 Student Records Management System
> A robust console-based application for managing academic records, built with a custom **2D Linked List (Multilist)** data structure to efficiently handle hierarchical data (Classes → Students).

## 💡 Project Overview (專案簡介)
This project implements a student management system without relying on high-level STL containers (like `std::vector` or `std::map`). Instead, it demonstrates low-level memory manipulation and data structure design by implementing a **dynamic Multilist**.

The system organizes data hierarchically:
1.  **Primary List**: Represents different 'Classes' (班級).
2.  **Secondary List**: Each Class node points to a linked list of 'Students' (學生).

## 🧩 Technical Highlights (技術亮點)
* **Custom Data Structure**: Implemented a "List of Lists" from scratch.
* **Memory Management**: Manual handling of dynamic allocation and deallocation to prevent memory leaks.
* **Efficient Traversal**: Algorithms optimized for searching within the 2D structure.

## 🏗️ Data Structure Design (架構設計)

[Head]
  ↓
[Class Node A] ────→ [Student 1] ────→ [Student 2] ────→ NULL
  ↓
[Class Node B] ────→ [Student 3] ────→ NULL
  ↓
[Class Node C] ────→ NULL
  ↓
 NULL
