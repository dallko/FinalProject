#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Employee {
    string id;
    string name;
    string department;
    double salary;
};

void addEmployee(ofstream& file, const Employee& emp) {
    file << emp.id << "," << emp.name << "," << emp.department << "," << emp.salary << "\n";
}

void displayEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No records found.\n";
        return;
    }
    cout << "ID      | Name            | Department | Salary\n";
    cout << "--------------------------------------------\n";
    for (const auto& emp : employees) {
        cout << setw(8) << emp.id << " | " << setw(15) << emp.name << " | "
                  << setw(10) << emp.department << " | " << setw(6) << fixed << setprecision(2) << emp.salary << "\n";
    }
}

vector<Employee> readEmployees(ifstream& file) {
    vector<Employee> employees;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name, department;
        double salary;
        char comma;
        if (iss >> id >> comma >> name >> comma >> department >> comma >> salary) {
            employees.push_back({id, name, department, salary});
        }
    }
    return employees;
}

void updateEmployeeSalary(ofstream& file, const string& id, double newSalary) {
    file.seekp(0, ios::beg);
    string line;
    ostringstream updatedFile;
    while (getline(file, line)) {
        istringstream iss(line);
        string currId, name, department;
        double salary;
        char comma;
        if (iss >> currId >> comma >> name >> comma >> department >> comma >> salary) {
            if (currId == id) {
                updatedFile << currId << "," << name << "," << department << "," << newSalary << "\n";
            } else {
                updatedFile << line << "\n";
            }
        }
    }
    file.seekp(0, ios::beg);
    file << updatedFile.str();
}

void deleteEmployee(ofstream& file, const string& id) {
    file.seekp(0, ios::beg);
    string line;
    ostringstream updatedFile;
    while (getline(file, line)) {
        istringstream iss(line);
        string currId, name, department;
        double salary;
        char comma;
        if (iss >> currId >> comma >> name >> comma >> department >> comma >> salary) {
            if (currId != id) {
                updatedFile << line << "\n";
            }
        }
    }
    file.seekp(0, ios::beg);
    file << updatedFile.str();
}

int main() {
    fstream dataFile("employee_data.csv", ios::in | ios::out | ios::app);

    if (!dataFile.is_open()) {
        cerr << "Error: Unable to open file for reading and writing.\n";
        return 1;
    }

    vector<Employee> employees = readEmployees(dataFile);

    int choice;
    string id, name, department;
    double salary;

    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employees\n";
        cout << "3. Update Employee Salary\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID, Name, Department, Salary: ";
                cin >> id >> name >> department >> salary;
                addEmployee(dataFile, {id, name, department, salary});
                break;
            case 2:
                displayEmployees(employees);
                break;
            case 3:
                cout << "Enter ID of employee to update salary: ";
                cin >> id;
                cout << "Enter new salary: ";
                cin >> salary;
                updateEmployeeSalary(dataFile, id, salary);
                break;
            case 4:
                cout << "Enter ID of employee to delete: ";
                cin >> id;
                deleteEmployee(dataFile, id);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    dataFile.close();
    return 0;
}
