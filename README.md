# ViewSync Platform
## Streaming Video Network Syndication Mesh

ViewSync Platform is a Data Structures and Algorithms (DSA) based C++ application that simulates the core functionalities of a modern video streaming platform. The project demonstrates how various DSA concepts can be applied to solve real-world problems such as content management, viewing history tracking, task scheduling, license verification, content analytics, network routing, and workload balancing.

---

## Problem Statement

Modern streaming platforms manage large volumes of content, subscriber interactions, licensing agreements, content delivery networks, and media processing tasks. Efficient handling of these operations requires the use of suitable Data Structures and Algorithms.

This project aims to simulate a streaming platform that can efficiently organize content, manage subscriber activities, process system tasks, verify licenses, analyze viewer engagement, optimize content delivery, and distribute encoding workloads.

---

## Objectives

- Apply Data Structures and Algorithms to a real-world application.
- Implement efficient content catalog management.
- Manage viewing history with rollback functionality.
- Process system tasks using queue scheduling.
- Verify content licenses using hash-based lookup.
- Rank clips based on viewer retention.
- Model content syndication networks using graphs.
- Compute shortest delivery routes using Dijkstra’s Algorithm.
- Balance encoding workloads using priority queues.
- Develop a menu-driven C++ application using STL.

---

## System Overview

The ViewSync Platform is divided into eight functional modules:

### Catalog Directory
Stores and organizes video metadata such as title, genre, category, tags, and licensing information.

### Correction Log
Maintains subscriber viewing state changes and supports undo operations.

### Algorithm Pipeline
Processes profile-related tasks in First-In-First-Out (FIFO) order.

### Registration Code
Stores and verifies publisher licensing information.

### Clip Sorter
Ranks streaming clips according to viewer retention.

### Syndication Grid
Represents content licensing and distribution platforms through a graph structure.

### Delivery Transport
Finds the minimum-cost route between content providers and end users.

### Frame Splitter
Distributes video encoding workloads among available processors.

### Architecture Overview

```text
Catalog Directory
        |
        v
Correction Log
        |
        v
Algorithm Pipeline
        |
        v
Registration Code


Syndication Grid
        |
        v
Delivery Transport
        |
        v
User Device


Frame Splitter
        |
        v
Encoding Workload Distribution
```

---

## Data Structures and Algorithms Used

| Module | Data Structure / Algorithm |
|----------|---------------------------|
| Catalog Directory | Vector, Unordered Map |
| Correction Log | Stack |
| Algorithm Pipeline | Queue |
| Registration Code | Unordered Map |
| Clip Sorter | STL Sort |
| Syndication Grid | Graph (Adjacency List) |
| Delivery Transport | Dijkstra's Algorithm |
| Frame Splitter | Priority Queue (Min Heap) |

### STL Components Used

- vector
- map
- unordered_map
- stack
- queue
- priority_queue
- sort

---

## Implementation Approach

### Catalog Directory
Video records are stored in vectors, while metadata indexing is maintained through unordered maps for efficient searching.

### Correction Log
Every viewing state modification is pushed onto a stack. Undo operations restore the previous state using stack pop operations.

### Algorithm Pipeline
Tasks are stored and processed using a queue to maintain FIFO scheduling.

### Registration Code
Licensing information is maintained using unordered maps to provide fast verification.

### Clip Sorter
Retention values are sorted in descending order using STL sort.

### Syndication Grid
A graph represented through adjacency lists models the content syndication network.

### Delivery Transport
Dijkstra’s Algorithm is used to compute the minimum-cost route between two platforms.

### Frame Splitter
A priority queue assigns workloads to the least-loaded processor, ensuring balanced scheduling.

---

## Time and Space Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|------------|----------------|------------------|
| Add Video | O(1) | O(n) |
| Search Video | O(1) Average | O(n) |
| Record Viewing State | O(1) | O(n) |
| Undo Viewing State | O(1) | O(n) |
| Add Pipeline Task | O(1) | O(n) |
| Process Pipeline Task | O(1) | O(n) |
| Verify License | O(1) Average | O(n) |
| Sort Clips | O(n log n) | O(n) |
| Add Graph Edge | O(1) | O(V + E) |
| Dijkstra Algorithm | O((V + E) log V) | O(V) |
| Frame Scheduling | O(n log p) | O(n) |

Where:

- n = Number of records
- V = Number of vertices
- E = Number of edges
- p = Number of processors

---

## Execution Steps

### Compile Using Clang++

```bash
clang++ viewsync.cpp -o viewsync
```

### Run the Program

```bash
./viewsync
```

### Compile Using G++

```bash
g++ viewsync.cpp -o viewsync
./viewsync
```

---

## Sample Inputs and Outputs

### Main Menu

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

### Catalog Directory

```text
VIDEO CATALOG
------------------------------------------------------------
ID      TITLE               GENRE          CATEGORY
------------------------------------------------------------
101     Ocean Crimes        Thriller       Series
102     Galaxy Kids         Animation      Movie
103     Chef World          Reality        Show
------------------------------------------------------------
```

### Registration Code

```text
LICENSE VERIFICATION

License Code : LIC-NET-IND
Region       : India

Result : License Verified Successfully
```

### Clip Sorter

```text
CLIP RETENTION REPORT
------------------------------------------------------------
Rank    Clip Title                    Retention
------------------------------------------------------------
1       Chef World Finale             9.50
2       Ocean Crimes Opening          8.70
3       Galaxy Kids Trailer           6.20
------------------------------------------------------------
```

### Delivery Transport

```text
DELIVERY ROUTE REPORT
------------------------------------------------------------
Source      : Rights Holder
Destination : User Device
Total Cost  : 25

Route:
Rights Holder -> India CDN -> User Device
------------------------------------------------------------
```

### Frame Splitter

```text
FRAME SPLITTER REPORT
------------------------------------------------------------
Processor      Load
------------------------------------------------------------
1              14
2              13
3              10
------------------------------------------------------------
Total Encoding Time : 14
```

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

## Results and Observations

- Hash-based indexing enables efficient video and license lookup.
- Stack operations allow quick rollback of viewing state changes.
- Queue scheduling ensures FIFO task processing.
- Sorting effectively ranks clips based on viewer engagement.
- Graph structures accurately represent content distribution networks.
- Dijkstra’s Algorithm successfully computes optimal delivery routes.
- Priority queues efficiently balance encoding workloads.
- Multiple DSA concepts work together within a single integrated application.

---

## Conclusion

The ViewSync Platform successfully demonstrates the practical application of Data Structures and Algorithms in a streaming platform environment.

The project integrates vectors, hash maps, stacks, queues, sorting algorithms, graphs, Dijkstra’s Algorithm, and priority queues to solve real-world challenges related to content management, analytics, routing, and workload scheduling.

This implementation highlights how fundamental DSA concepts can be used to build efficient and scalable systems similar to those used by modern streaming services.

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

## Author

Sanika Kangane  
B.Tech CSE (2025–2029)  
ITM Skills University

---

## Course Information

Course: Data Structures and Algorithms with C++  
Project Type: DSA Case Study Project  
University: ITM Skills University

---

## Acknowledgement

This project was developed as part of the Data Structures and Algorithms coursework. The implementation focuses on applying fundamental DSA concepts to solve practical challenges faced by modern video streaming platforms.
