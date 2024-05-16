#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Employee {
    int id;
    string name;
    int age;
    string role;
    int performanceScore; 
};

// Функция для сохранения данных сотрудников в файл
void saveData(const vector<Employee>& employees, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& employee : employees) {
            file << employee.id << " " << employee.name << " " << employee.age << " " << employee.role << " " << employee.performanceScore << "\n";
        }
        file.close();
        cout << "Data saved successfully.\n\n";
    } else {
        cout << "Unable to open file to save data.\n\n";
    }
}

// Функция для загрузки данных сотрудников из файла
void loadData(vector<Employee>& employees, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        employees.clear(); // Очистка существующих данных перед загрузкой
        Employee employee;
        while (file >> employee.id >> employee.name >> employee.age >> employee.role >> employee.performanceScore) {
            employees.push_back(employee);
        }
        file.close();
        cout << "Data loaded successfully.\n\n";
    } else {
        cout << "Unable to open file to load data. Starting with an empty database.\n\n";
    }
}

void addEmployee(vector<Employee>& employees) {
    Employee newEmployee;
    cout << "Enter Employee ID: ";
    cin >> newEmployee.id;
    cout << "Enter Employee Name: ";
    cin.ignore(); // Игнорировать оставшийся символ новой строки от предыдущего ввода
    getline(cin, newEmployee.name);
    cout << "Enter Employee Age: ";
    cin >> newEmployee.age;
    cout << "Enter Employee Role: ";
    cin.ignore();
    getline(cin, newEmployee.role);
    cout << "Enter Employee Performance Score: ";
    cin >> newEmployee.performanceScore;
    employees.push_back(newEmployee);
    cout << "Employee added successfully.\n\n";
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
        cout << "Employee with ID " << id << " deleted.\n\n";
    } else {
        cout << "Employee with ID " << id << " not found.\n\n";
    }
}

void displayEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to display.\n\n";
        return;
    }

    cout << "Employees:\n";
    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << "\n";
        cout << "Name: " << employee.name << "\n";
        cout << "Age: " << employee.age << "\n";
        cout << "Role: " << employee.role << "\n";
        cout << "Performance Score: " << employee.performanceScore << "\n"; // Отображение оценки производительности
        cout << "---------------------\n\n";
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
        cout << "Performance Score of Employee with ID " << id << " updated.\n\n";
    } else {
        cout << "Employee with ID " << id << " not found.\n\n";
    }
}

void displayPerformanceScores(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to display performance scores.\n\n";
        return;
    }

    cout << "Performance Scores:\n";
    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << ", Name: " << employee.name << ", Performance Score: " << employee.performanceScore << "\n";
    }
    cout << endl;
}

int main() {
    vector<Employee> employees;
    int choice;
    const string filename = "employees.txt";

    // Загрузка существующих данных из файла
    loadData(employees, filename);

    while (true) {
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employees\n";
        cout << "4. Update Performance Score\n"; 
        cout << "5. Display Performance Scores\n"; 
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
                // Сохранение данных в файл перед выходом
                saveData(employees, filename);
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n\n";
        }
    }
}
