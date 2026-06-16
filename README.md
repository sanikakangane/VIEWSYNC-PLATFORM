# ViewSync Platform
### Streaming Video Network Syndication Mesh

A Data Structures & Algorithms (DSA) based C++ project that simulates a modern video streaming platform similar to Netflix, Disney+, and Amazon Prime Video.

The project demonstrates the practical implementation of core DSA concepts including Hash Maps, Stacks, Queues, Graphs, Sorting, Priority Queues, Greedy Scheduling, and Dijkstra's Algorithm to solve real-world streaming platform challenges.

---

## Problem Statement

ViewSync is a video streaming platform that manages a global catalog of licensed content, tracks subscriber viewing history, processes profile updates, verifies publisher licenses, ranks clips by retention, maintains a global licensing network, finds optimal content delivery routes, and distributes encoding workloads efficiently.

The system is designed using appropriate Data Structures and Algorithms to provide fast searching, reliable rollback operations, sequential task processing, quick license verification, optimized routing, and balanced workload distribution.

---

## Features

### 1. Catalog Directory

Organizes and classifies the complete video catalog using metadata.

#### Operations
- Add Video Metadata
- Search Videos by Genre
- Search Videos by Category
- Search Videos by Tag
- Display Complete Catalog

#### Data Structures Used
- Vector
- Unordered Map

---

### 2. Correction Log

Maintains subscriber viewing history changes and supports rollback.

#### Operations
- Record Viewing State Change
- Undo Last Viewing State Change
- Display Current Viewing States

#### Data Structure Used
- Stack

---

### 3. Algorithm Pipeline

Processes profile-related tasks in the order they arrive.

#### Operations
- Add Profile Processing Task
- Process Next Task
- Display Pending Tasks

#### Data Structure Used
- Queue

---

### 4. Registration Code

Stores and validates publisher licensing information.

#### Operations
- Add License Code
- Verify License by Region
- Display Registered Licenses

#### Data Structure Used
- Unordered Map

---

### 5. Clip Sorter

Ranks streaming clips according to viewer retention.

#### Operations
- Add Clip Retention Data
- Sort Clips by Retention
- Display Ranked Clips

#### Algorithm Used
- STL Sort

---

### 6. Syndication Grid

Represents global licensing platforms and their connections.

#### Operations
- Add Licensing Platform
- Add Licensing Connection
- Display Syndication Network

#### Data Structure Used
- Graph (Adjacency List)

---

### 7. Delivery Transport

Finds the lowest-cost content delivery route.

#### Operations
- Select Source Platform
- Select Destination Platform
- Calculate Lowest Cost Path

#### Algorithms Used
- Dijkstra's Algorithm
- Priority Queue

---

### 8. Frame Splitter

Distributes video encoding workloads across processors.

#### Operations
- Add Frame Encoding Times
- Assign Frames to Processors
- Display Load Distribution

#### Data Structures Used
- Priority Queue (Min Heap)
- Vector

#### Algorithm Used
- Greedy Scheduling

---

## Data Structures Used

| Module | Data Structure |
|----------|---------------|
| Catalog Directory | Vector, Unordered Map |
| Correction Log | Stack |
| Algorithm Pipeline | Queue |
| Registration Code | Unordered Map |
| Clip Sorter | Vector + Sorting |
| Syndication Grid | Graph (Adjacency List) |
| Delivery Transport | Priority Queue |
| Frame Splitter | Priority Queue (Min Heap) |

---

## Algorithms Used

- Hash-based Searching using Unordered Map
- STL Sort
- Graph Representation using Adjacency List
- Dijkstra's Shortest Path Algorithm
- Greedy Load Balancing
- Priority Queue Scheduling

---

## DSA Concepts Demonstrated

- Arrays and Vectors
- Hash Maps
- Stack
- Queue
- Graph
- Priority Queue
- Greedy Algorithm
- Sorting
- Dijkstra's Algorithm
- Search Optimization
- Scheduling Techniques

---

## Sample Output

```text
============================================================
                    VIEWSYNC PLATFORM
         Streaming Video Network Syndication Mesh
============================================================

MAIN MENU
------------------------------------------------------------
1. Catalog Directory
2. Correction Log
3. Algorithm Pipeline
4. Registration Code
5. Clip Sorter
6. Syndication Grid
7. Delivery Transport
8. Frame Splitter
0. Exit
------------------------------------------------------------
```

---

## Repository Structure

```text
VIEWSYNC-PLATFORM/
│
├── viewsync.cpp
├── README.md
└── ViewSync_DSA_Project_Report.pdf
```

---

## Compilation & Execution

### Using Clang++

```bash
clang++ viewsync.cpp -o viewsync
./viewsync
```

### Using G++

```bash
g++ viewsync.cpp -o viewsync
./viewsync
```

---

## Real-World Mapping

| ViewSync Module | Real-World Equivalent |
|-----------------|----------------------|
| Catalog Directory | Netflix Content Catalog |
| Correction Log | Watch History Management |
| Algorithm Pipeline | Recommendation Engine Tasks |
| Registration Code | Content License Verification |
| Clip Sorter | Viewer Retention Analytics |
| Syndication Grid | Global CDN & Licensing Network |
| Delivery Transport | Content Delivery Optimization |
| Frame Splitter | Video Encoding Cluster |

---

## Sample Data Included

### Videos
- Ocean Crimes
- Galaxy Kids
- Chef World

### Licenses
- LIC-NET-IND
- LIC-DIS-USA
- LIC-AMZ-GLB

### Platforms
- Rights Holder
- India CDN
- Global CDN
- User Device

### Clips
- Ocean Crimes Opening
- Galaxy Kids Trailer
- Chef World Finale

---

## Learning Outcomes

This project demonstrates practical applications of:

- Data Structures and Algorithms
- Hashing Techniques
- Stack-based Rollback Systems
- Queue-based Task Scheduling
- Graph Modeling
- Shortest Path Optimization
- Sorting and Ranking Systems
- Load Balancing Techniques
- Real-world System Design using DSA

---

## Author

**Sanika Kangane**  
B.Tech CSE (2025–2029)  
ITM Skills University

---

## Course Information

**Course:** Data Structures & Algorithms with C++  
**Semester:** II  
**University:** ITM Skills University

---

## Acknowledgement

This project was developed as part of the academic coursework for Data Structures & Algorithms with C++. The implementation focuses on applying fundamental DSA concepts to solve real-world challenges faced by modern video streaming platforms.
