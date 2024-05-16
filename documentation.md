# Employee Management System Documentation

## Purpose:
The purpose of this project is to create a simple employee management system using C++. The system allows users to add, delete, display, and update performance scores of employees. It also provides functionality to persistently store employee data in a file, ensuring that the data is remembered even if the program stops running.

## Design Decisions:
- **Data Structure**: The main data structure used in this project is a vector of Employee structs to store employee information.
- **File Handling**: To ensure data persistence, file handling functions were implemented to save and load employee data from a text file.
- **User Interface**: The user interface is implemented using console input and output, providing a simple command-line interface for users to interact with the system.

## Algorithms Used:
- **Search Algorithm**: The find_if algorithm from the `<algorithm>` library is used to search for an employee by ID.
- **Serialization and Deserialization**: The data is serialized to a file when saving and deserialized when loading, allowing for persistent storage and retrieval of employee data.

## Functions/Modules Created:
- `saveData`: Saves the current state of employee data to a file.
- `loadData`: Loads existing employee data from a file at the start of the program.
- `addEmployee`: Adds a new employee to the system.
- `deleteEmployee`: Deletes an employee from the system based on ID.
- `displayEmployees`: Displays the details of all employees in the system.
- `updatePerformanceScore`: Updates the performance score of an employee based on ID.
- `displayPerformanceScores`: Displays the performance scores of all employees in the system.

## How to Use the Software:
1. Compile the provided C++ code using a C++ compiler.
2. Run the compiled executable.
3. Follow the on-screen menu prompts to perform various operations such as adding, deleting, displaying employees, updating performance scores, or exiting the program.
4. The data will be automatically saved to a file named "employees.txt" when exiting the program and loaded from the same file when starting the program again.

## Installation or Setup Instructions:
- Ensure you have a C++ compiler installed on your system.
- Download the provided C++ source code file.
- Compile the code using your C++ compiler.
- Run the compiled executable to start the employee management system.

