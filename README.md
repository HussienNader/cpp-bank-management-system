# 💳 C++ Bank Management System

> A feature-rich C++ banking management system built throughout my learning journey, demonstrating file handling, modular programming, authentication, role-based permissions, Object-Oriented Programming, reusable utility components, and console application design.

---

## 📖 Overview

This project is a **console-based Bank Management System** developed in **C++** as part of my programming journey.

The project was not created in a single phase. It evolved over an extended period as I learned new C++ concepts and gradually expanded the original application.

The project currently contains **two major versions**:

* **Version 1 — Procedural Programming**
* **Version 2 — Object-Oriented Programming**

Version 2 represents a major step in the evolution of the project. The same general banking system was revisited and redesigned using classes, inheritance, reusable components, and a more organized multi-module structure.

The original source code has been intentionally preserved to reflect the development of the project and my progression as a C++ programmer.

---

# 🧭 Project Evolution

```text
Version 1
Procedural C++
      │
      │  Learning and expanding the system
      ▼
Version 2
Object-Oriented C++
      │
      ├── Classes and Objects
      ├── Inheritance
      ├── Reusable Screen Classes
      ├── Utility Components
      ├── User Management
      ├── Transactions
      ├── Transfers
      └── Currency Exchange
```

---

# 🏦 Version 1 — Procedural Bank Management System

The first version was developed using traditional procedural C++ techniques.

It focused on learning how to build a complete console application using functions, structures, vectors, enums, file handling, and menu-driven programming.

### Main Features

* Client List
* Add Client
* Delete Client
* Update Client
* Find Client
* Deposit
* Withdraw
* Total Balances
* User Login
* User Management
* Permission System
* ATM Simulation
* File-based data storage

The original version represents the foundation on which the later version was built.

---

# 🧱 Version 2 — Object-Oriented Bank Management System

Version 2 is a later evolution of the same project, redesigned using **Object-Oriented Programming**.

The project introduces classes for entities, screens, utilities, transactions, and other parts of the application.

### Core Classes

Some of the main classes include:

* `clsPerson`
* `clsBankClient`
* `clsUser`
* `clsScreen`
* `clsMainScreen`
* `clsLoginScreen`
* `clsDate`
* `clsString`
* `clsUtil`
* `clsInputValidate`

The application also contains separate screen classes for different operations, making the project more modular than the original procedural version.

---

# 👥 Client Management

The OOP version includes dedicated screens and classes for client operations:

* List Clients
* Add New Client
* Delete Client
* Update Client
* Find Client

Client-related functionality is separated into dedicated components rather than being concentrated in one large procedural module.

---

# 👤 User Management

The project includes a complete user-management section with:

* User List
* Add User
* Delete User
* Update User
* Find User
* User Login
* User Permissions
* Access Control

The user system is represented through the `clsUser` class and related management screens.

---

# 💰 Transactions

The banking transaction system was expanded in Version 2.

It includes:

* Deposit
* Withdraw
* Transfer
* Transfer Log
* Total Balances

Each major transaction area has its own screen class.

---

# 💱 Currency Exchange

Version 2 also introduces a **Currency Exchange** subsystem.

It includes:

* List Currencies
* Find Currency
* Update Currency
* Calculate Currency Exchange
* Currency Exchange screen

The currency functionality is organized into separate classes under the `CurrencyExchange` section.

---

# 🧩 Reusable Utility Components

One of the important parts of Version 2 is the creation of several **reusable utility classes**.

These components were developed independently of the banking logic and can be reused in other C++ projects.

## `clsDate`

A reusable date-handling class providing functionality related to:

* Creating dates
* Reading the system date
* Formatting dates
* Validating dates
* Leap-year calculations
* Days, hours, minutes, and seconds calculations
* Other date-related operations

The class can be used independently in applications that require date manipulation.

---

## `clsString`

A reusable string utility class providing common string operations such as:

* String length
* Word counting
* Letter counting
* Uppercase and lowercase conversion
* Letter-case inversion
* String splitting
* Other string-related operations

The class is designed to provide reusable string functionality across different projects.

---

## `clsUtil`

A general-purpose utility class containing reusable helper functionality such as:

* Random number generation
* Random character generation
* Random word generation
* Random key generation
* Array filling
* Value swapping
* Array shuffling
* Other utility operations

These functions are independent from the banking domain and can be useful in many different applications.

---

# 🧬 Object-Oriented Concepts Demonstrated

Version 2 demonstrates several important OOP concepts through the project structure.

### Classes and Objects

The project separates entities and application components into classes such as:

* `clsPerson`
* `clsBankClient`
* `clsUser`
* `clsCurrency`

### Inheritance

Some classes inherit from common base classes.

For example:

```text
clsPerson
   │
   ├── clsBankClient
   │
   └── clsUser
```

Screen classes also inherit common functionality from `clsScreen`.

### Encapsulation

Data and the operations that work with that data are grouped inside classes.

### Modular Design

Different responsibilities are separated into different classes and folders, including:

* Client management
* User management
* Transactions
* Currency exchange
* Screen management
* Utility functionality

---

# 💾 Data Storage

The project uses **text files as a simple file-based data store**.

Version 2 includes data files for areas such as:

* Clients
* Users
* Currencies
* Login/Register information
* Transfer records

This approach was used as part of the learning process to practice file handling and persistent data storage without relying on an external database.

---

# 🗂 Project Structure

The repository contains both versions of the project:

```text
cpp-bank-management-system
│
├── Version 1
│   └── Procedural Bank Management System
│
├── Version-2-OOP
│   └── Object-Oriented Bank Management System
│       │
│       ├── Client Management
│       ├── User Management
│       ├── Transactions
│       ├── Currency Exchange
│       ├── Reusable Utility Components
│       └── Data Files
│
├── README.md
└── LICENSE
```

The Version 2 folder preserves the internal organization used during the development of the project.

---

# 🛠 Technologies and Concepts

* C++
* Object-Oriented Programming
* Procedural Programming
* Standard Template Library (STL)
* File Handling
* Classes and Objects
* Inheritance
* Encapsulation
* Structures
* Enums
* Vectors
* Console Application Development
* Authentication
* Authorization
* Role-Based Permissions
* Modular Programming

---

# 📚 What I Learned

This project helped me progress from basic procedural programming toward a more object-oriented approach.

Throughout the different phases, I practiced:

* Building complete console applications
* Working with files and persistent data
* Designing CRUD operations
* Creating classes and objects
* Using inheritance
* Separating responsibilities between classes
* Building reusable utility components
* Implementing authentication
* Implementing role-based permissions
* Creating transaction workflows
* Organizing larger C++ projects into multiple files and folders
* Reusing common functionality across different parts of an application

---

# 📝 Project History

This project was developed over a long period and through multiple learning phases.

The first version was created while I was learning procedural C++. As I learned more advanced concepts, especially Object-Oriented Programming, I revisited the same project and developed a new version using classes, inheritance, reusable components, and a more structured architecture.

Rather than replacing the original implementation, both versions are preserved in this repository.

This allows the repository to demonstrate the evolution of the project from:

**Procedural C++ → Object-Oriented C++**

The code has intentionally been preserved as a record of that learning journey rather than being completely refactored into a modern production architecture.

---

# 🚀 Future Development

Possible future directions for the project may include:

* Further architectural improvements
* More reusable components
* Additional banking functionality
* Database integration
* Improved testing
* Graphical user interface
* Further exploration of modern C++ techniques

These are possible directions rather than completed features.

---

# ▶️ Running the Project

The project is a C++ console application.

To run Version 2:

1. Open the Version 2 project in a C++ development environment.
2. Make sure the required source files and data files maintain their relative locations.
3. Build the project.
4. Run the application through the console.

---

# 📸 Screenshots

Screenshots will be added to demonstrate the main areas of the application, including:

* Login
* Main Menu
* Client Management
* User Management
* Transactions
* Transfer System
* Currency Exchange

---

# 📄 License

This project is published for educational and portfolio purposes under the **MIT License**.

See [LICENSE](LICENSE) for details.

---

# 👤 Author

**Hussien Nader**

This repository documents my progression through C++ programming, from procedural programming to Object-Oriented Programming and reusable software components.
