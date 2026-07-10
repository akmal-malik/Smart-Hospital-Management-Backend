# 🏥 Smart Hospital Management Backend (C++)

![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux-lightgrey)
![Architecture](https://img.shields.io/badge/Architecture-Object%20Oriented-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

---

# 📖 Project Overview

The **Smart Hospital Management Backend** is a modular backend system developed in **Modern C++** that simulates the core services of a smart hospital.

The project focuses on solving real-world hospital management problems using efficient **Data Structures**, **Algorithms**, and **Object-Oriented Programming** principles.

Instead of simply storing information, the backend intelligently:

* Detects duplicate patients using fuzzy string matching
* Allocates blood units using **FEFO (First Expire First Out)**
* Finds the fastest hospital route using **Dijkstra's Algorithm**
* Verifies digital medical certificates using **cryptographic hashing**
* Persists all hospital data using file handling

The entire project is implemented from scratch without external frameworks, making it an excellent demonstration of backend software engineering using C++.

---

# 🎯 Problem Statement

Modern hospitals manage thousands of patients, blood units, certificates, and internal logistics every day.

Traditional systems often suffer from problems such as:

* Duplicate patient registrations
* Blood wastage due to poor allocation strategies
* Slow emergency navigation inside hospitals
* Manual verification of medical certificates
* Lack of centralized persistent storage
* Poor modularity and maintainability

The goal of this project is to build a modular backend capable of solving these challenges efficiently using algorithms and data structures.

---

# 💡 Proposed Solution

The backend is divided into independent modules, each solving a specific hospital management problem.

### Patient Management

Maintains patient records with duplicate detection using Levenshtein Distance.

### Blood Bank Management

Stores blood units using a **Priority Queue (Min Heap)** sorted by expiry date to implement **FEFO (First Expire First Out)**.

### Hospital Router

Represents the hospital as a graph and computes the fastest route using **Dijkstra's Shortest Path Algorithm**.

### Digital Certificate Verification

Generates secure hashes for certificates and detects tampering during verification.

### Hospital Service Layer

Acts as the central controller that integrates all modules into a single backend.

---

# 🚀 Features

## 👨‍⚕️ Patient Management

* Register new patients
* Search patient by ID
* Search patient by phone number
* Search patient by name (fuzzy matching)
* Update patient details
* Delete patient
* Duplicate patient detection
* Persistent storage

---

## 🩸 Blood Bank Management

* Add blood units
* Allocate blood units
* FEFO allocation
* Remove expired blood units
* Search blood units
* Update expiry date
* Remove blood units
* Low stock detection
* Inventory statistics
* Persistent storage

---

## 🏥 Hospital Routing

* Hospital represented as Graph
* Add corridors
* Remove corridors
* Block corridors
* Unblock corridors
* AI traffic updates
* Reset traffic
* Display hospital map
* Fastest route calculation
* Route time calculation
* Persistent storage

---

## 📄 Digital Certificate Manager

* Generate digital certificates
* Verify certificates
* Search certificates
* Delete certificates
* Persistent storage
* Digital hash verification

---

## 📊 Hospital Dashboard

Displays

* Total Patients
* Total Blood Units
* Total Certificates

---

# 🧠 Data Structures Used

| Data Structure            | Purpose                                |
| ------------------------- | -------------------------------------- |
| Vector                    | Patient database, certificate database |
| Unordered Map             | Blood inventory by blood group         |
| Priority Queue (Min Heap) | FEFO blood allocation                  |
| Graph (Adjacency List)    | Hospital routing                       |
| Queue                     | Dijkstra implementation                |
| Pair                      | Priority queue for shortest path       |

---

# ⚙️ Algorithms Used

## 1. Dijkstra's Algorithm

Used for computing the fastest route between two hospital locations.

Applications

* Emergency routing
* ICU navigation
* Ambulance movement

Time Complexity

```
O((V + E) log V)
```

---

## 2. FEFO (First Expire First Out)

Blood units are allocated according to the earliest expiry date.

Implemented using

```
Priority Queue (Min Heap)
```

Benefits

* Reduces blood wastage
* Ensures safe allocation

---

## 3. Levenshtein Distance

Used for duplicate patient detection.

Example

```
Akmal Malik
Akmal Malek
```

Distance is very small.

Registration is blocked.

Benefits

* Prevents duplicate patient records
* Handles spelling mistakes

---

## 4. Hashing

Medical certificates are converted into secure hashes.

During verification

```
Current Hash == Stored Hash
```

If hashes differ

```
Certificate Tampered
```

---

# 🏗️ Object-Oriented Design

The project follows OOP principles.

## Encapsulation

Each module hides its internal implementation.

Examples

* PatientManager
* BloodBankManager
* HospitalRouter

---

## Abstraction

Users interact through manager classes without knowing internal algorithms.

---

## Modularity

Each module is independent.

```
PatientManager

BloodBankManager

HospitalRouter

CertificateManager

HospitalService
```

---

# 📂 Project Structure

```
Hospital_Management_Backend/

│
├── include/
│   ├── Models.h
│   ├── Utils.h
│   ├── PatientManager.h
│   ├── BloodBankManager.h
│   ├── HospitalRouter.h
│   ├── CertificateManager.h
│   └── HospitalService.h
│
├── src/
│   ├── main.cpp
│   ├── Utils.cpp
│   ├── PatientManager.cpp
│   ├── BloodBankManager.cpp
│   ├── HospitalRouter.cpp
│   ├── CertificateManager.cpp
│   └── HospitalService.cpp
│
├── database/
│
├── README.md
├── .gitignore
└── LICENSE
```

---

# 💾 Persistent Storage

The backend automatically stores and restores data using text files.

```
patients.txt

blood_inventory.txt

hospital_map.txt

certificates.txt
```

Data is automatically loaded when the system starts and saved before shutdown.

---

# 🛡️ Validation Implemented

The backend validates:

### Patients

* Empty IDs
* Empty names
* Invalid phone numbers
* Duplicate registrations

### Blood Bank

* Duplicate blood unit IDs
* Invalid blood groups
* Invalid requests

### Hospital Router

* Invalid node numbers
* Duplicate corridors
* Negative travel time
* Self-loops

### Certificates

* Duplicate certificates
* Hash verification

---

# 📈 Time Complexity

| Operation          | Complexity     |
| ------------------ | -------------- |
| Register Patient   | O(n)           |
| Search Patient     | O(n)           |
| Blood Allocation   | O(log n)       |
| Add Blood Unit     | O(log n)       |
| Remove Blood Unit  | O(n log n)     |
| Update Blood Unit  | O(n log n)     |
| Dijkstra Routing   | O((V+E) log V) |
| Certificate Search | O(n)           |
| Hash Generation    | O(k)           |

---

# ▶️ Build Instructions

Compile

```bash
clang++ -std=c++17 -Iinclude src/*.cpp -o hospital
```

Run

```bash
./hospital
```

---

# ✅ Sample Output

```
CITY HOSPITAL MANAGEMENT BACKEND

[SYSTEM] All modules loaded successfully.

Patient Found : Akmal Malik

Allocated Unit : B-002

Route :
0 1 2 3 4

Certificate Hash :
cd36edf257305dbc

Dashboard

Patients : 1
Blood Units : 3
Certificates : 3

Backend Test Completed Successfully.
```

---

# 🔮 Future Improvements

* MySQL Database Integration
* REST API
* JWT Authentication
* Role Based Access Control
* Appointment Scheduling
* Doctor Management
* Billing Module
* Inventory Analytics
* Emergency Prediction using AI
* GUI using Qt
* Web Dashboard
* Cloud Deployment
* Docker Support
* Unit Testing
* Multi-threading

---

# 📚 Concepts Demonstrated

* Object-Oriented Programming
* Data Structures
* Algorithms
* Graph Theory
* Priority Queue
* Hashing
* File Handling
* Modular Software Design
* Backend Development
* Error Handling
* Data Validation

---

# 👨‍💻 Author

**Mohammad Akmal**

BCA Student
Lovely Professional University

**Skills**

* C++
* Data Structures & Algorithms
* Object-Oriented Programming
* SQL
* Python
* Backend Development

---

# ⭐ Repository

If you found this project useful, consider giving it a ⭐ on GitHub.

It helps others discover the project and supports future development.
