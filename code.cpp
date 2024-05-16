#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Employee {
    int id;
    string name;
    int age;
    string role;
    int performanceScore; // New field for performance evaluation
};

void addEmployee(vector<Employee>& employees) {
    Employee newEmployee;
    cout << "Enter Employee ID: ";
    cin >> newEmployee.id;
    cout << "Enter Employee Name: ";
    cin.ignore(); // Ignore any remaining newline character from previous input
    getline(cin, newEmployee.name);
    cout << "Enter Employee Age: ";
    cin >> newEmployee.age;
    cout << "Enter Employee Role: ";
    cin.ignore();
    getline(cin, newEmployee.role);
    cout << "Enter Employee Performance Score: ";
    cin >> newEmployee.performanceScore;
    employees.push_back(newEmployee);
}

void deleteEmployee(vector<Employee>& employees) {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    auto it = find_if(employees.begin(), employees.end(), [&id](const Employee& e) {
        return e.id == id;
    });

    if (it != employees.end()) {
        employees.erase(it);
        cout << "Employee with ID " << id << " deleted.\n";
    } else {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

void displayEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to display.\n";
        return;
    }

    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << "\n";
        cout << "Name: " << employee.name << "\n";
        cout << "Age: " << employee.age << "\n";
        cout << "Role: " << employee.role << "\n";
        cout << "Performance Score: " << employee.performanceScore << "\n"; // Display performance score
        cout << "---------------------\n";
    }
}

void updatePerformanceScore(vector<Employee>& employees) {
    int id, newScore;
    cout << "Enter Employee ID to update performance score: ";
    cin >> id;
    cout << "Enter new Performance Score: ";
    cin >> newScore;

    auto it = find_if(employees.begin(), employees.end(), [&id](const Employee& e) {
        return e.id == id;
    });

    if (it != employees.end()) {
        it->performanceScore = newScore;
        cout << "Performance Score of Employee with ID " << id << " updated.\n";
    } else {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

void displayPerformanceScores(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to display performance scores.\n";
        return;
    }

    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << ", Name: " << employee.name << ", Performance Score: " << employee.performanceScore << "\n";
    }
}

int main() {
    vector<Employee> employees;
    int choice;

    while (true) {
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employees\n";
        cout << "4. Update Performance Score\n"; // New option for updating performance score
        cout << "5. Display Performance Scores\n"; // New option for displaying performance scores
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(employees);
                break;
            case 2:
                deleteEmployee(employees);
                break;
            case 3:
                displayEmployees(employees);
                break;
            case 4:
                updatePerformanceScore(employees);
                break;
            case 5:
                displayPerformanceScores(employees);
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
