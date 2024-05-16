#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Include this header for std::find_if

using namespace std;

struct Employee {
    int id;
    string name;
    int age;
    string role;
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
        cout << "---------------------\n";
    }
}

int main() {
    vector<Employee> employees;
    int choice;

    while (true) {
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employees\n";
        cout << "4. Exit\n";
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
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
