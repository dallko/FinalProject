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
    int performanceScore; // Новое поле для оценки производительности
};

// Функция для сохранения данных о сотрудниках в файл
void saveData(const vector<Employee>& employees, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& employee : employees) {
            file << employee.id << " " << employee.name << " " << employee.age << " " << employee.role << " " << employee.performanceScore << "\n";
        }
        file.close();
        cout << "Данные успешно сохранены.\n\n";
    } else {
        cout << "Не удалось открыть файл для сохранения данных.\n\n";
    }
}

// Функция для загрузки данных о сотрудниках из файла
void loadData(vector<Employee>& employees, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        employees.clear(); // Очистка существующих данных перед загрузкой
        Employee employee;
        while (file >> employee.id >> employee.name >> employee.age >> employee.role >> employee.performanceScore) {
            employees.push_back(employee);
        }
        file.close();
        cout << "Данные успешно загружены.\n\n";
    } else {
        cout << "Не удалось открыть файл для загрузки данных. Начало работы с пустой базой данных.\n\n";
    }
}

void addEmployee(vector<Employee>& employees) {
    Employee newEmployee;
    cout << "Введите ID сотрудника: ";
    cin >> newEmployee.id;
    cout << "Введите имя сотрудника: ";
    cin.ignore(); // Игнорировать любые оставшиеся символы новой строки от предыдущего ввода
    getline(cin, newEmployee.name);
    cout << "Введите возраст сотрудника: ";
    cin >> newEmployee.age;
    cout << "Введите роль сотрудника: ";
    cin.ignore();
    getline(cin, newEmployee.role);
    cout << "Введите оценку производительности сотрудника: ";
    cin >> newEmployee.performanceScore;
    employees.push_back(newEmployee);
    cout << "Сотрудник успешно добавлен.\n\n";
}

void deleteEmployee(vector<Employee>& employees) {
    int id;
    cout << "Введите ID сотрудника для удаления: ";
    cin >> id;

    auto it = find_if(employees.begin(), employees.end(), [&id](const Employee& e) {
        return e.id == id;
    });

    if (it != employees.end()) {
        employees.erase(it);
        cout << "Сотрудник с ID " << id << " удален.\n\n";
    } else {
        cout << "Сотрудник с ID " << id << " не найден.\n\n";
    }
}

void displayEmployees(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "Нет сотрудников для отображения.\n\n";
        return;
    }

    cout << "Сотрудники:\n";
    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << "\n";
        cout << "Имя: " << employee.name << "\n";
        cout << "Возраст: " << employee.age << "\n";
        cout << "Роль: " << employee.role << "\n";
        cout << "Оценка производительности: " << employee.performanceScore << "\n"; // Отображение оценки производительности
        cout << "---------------------\n\n";
    }
}

void updatePerformanceScore(vector<Employee>& employees) {
    int id, newScore;
    cout << "Введите ID сотрудника для обновления оценки производительности: ";
    cin >> id;
    cout << "Введите новую оценку производительности: ";
    cin >> newScore;

    auto it = find_if(employees.begin(), employees.end(), [&id](const Employee& e) {
        return e.id == id;
    });

    if (it != employees.end()) {
        it->performanceScore = newScore;
        cout << "Оценка производительности сотрудника с ID " << id << " обновлена.\n\n";
    } else {
        cout << "Сотрудник с ID " << id << " не найден.\n\n";
    }
}

void displayPerformanceScores(const vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "Нет сотрудников для отображения оценок производительности.\n\n";
        return;
    }

    cout << "Оценки производительности:\n";
    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << ", Имя: " << employee.name << ", Оценка производительности: " << employee.performanceScore << "\n";
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
        cout << "1. Добавить сотрудника\n";
        cout << "2. Удалить сотрудника\n";
        cout << "3. Отобразить список сотрудников\n";
        cout << "4. Обновить оценку производительности\n";
        cout << "5. Отобразить оценки производительности\n"; 
        cout << "6. Выйти\n";
        cout << "Введите ваш выбор: ";
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
                cout << "Завершение работы программы.\n";
                return 0;
            default:
                cout
