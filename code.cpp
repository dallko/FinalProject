#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string fileName = "Employee.txt";

class Employee {
private:
    int EmpID;
    string EmpName;
    string Job;
    float Salary;
    vector<string> PerformanceEvaluations;

public:
    void ReadData();
    int GetID() const;
    void DisplayRecord() const;
    void AddPerformanceEvaluation();
    void DisplayPerformanceEvaluations() const;
    friend ofstream& operator<<(ofstream& ofs, const Employee& emp);
    friend ifstream& operator>>(ifstream& ifs, Employee& emp);
};

void Employee::ReadData() {
    cout << "\nEmployee ID: ";
    cin >> EmpID;
    cin.ignore();
    cout << "Employee Name: ";
    getline(cin, EmpName);
    cout << "Employee's job: ";
    getline(cin, Job);
    cout << "Salary: ";
    cin >> Salary;
}

void Employee::DisplayRecord() const {
    cout << "\n";
    cout << setw(5) << EmpID << setw(15) << EmpName << setw(15) << Job << setw(8) << Salary;
}

int Employee::GetID() const {
    return EmpID;
}

void Employee::AddPerformanceEvaluation() {
    string evaluation;
    cout << "Enter performance evaluation 1-10: ";
    cin.ignore();
    getline(cin, evaluation);
    PerformanceEvaluations.push_back(evaluation);
    cout << "Performance evaluation added successfully.";
}

void Employee::DisplayPerformanceEvaluations() const {
    cout << "\nPerformance Evaluations for " << EmpName << " (ID: " << EmpID << "):";
    if (PerformanceEvaluations.empty()) {
        cout << "\nNo evaluations available.";
    } else {
        for (const auto& evaluation : PerformanceEvaluations) {
            cout << "\n- " << evaluation;
        }
    }
}

ofstream& operator<<(ofstream& ofs, const Employee& emp) {
    ofs << emp.EmpID << '\n'
        << emp.EmpName << '\n'
        << emp.Job << '\n'
        << emp.Salary << '\n';
    ofs << emp.PerformanceEvaluations.size() << '\n';
    for (const auto& eval : emp.PerformanceEvaluations) {
        ofs << eval << '\n';
    }
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Employee& emp) {
    size_t evalCount;
    ifs >> emp.EmpID;
    ifs.ignore();
    getline(ifs, emp.EmpName);
    getline(ifs, emp.Job);
    ifs >> emp.Salary;
    ifs >> evalCount;
    ifs.ignore();
    emp.PerformanceEvaluations.clear();
    for (size_t i = 0; i < evalCount; ++i) {
        string eval;
        getline(ifs, eval);
        emp.PerformanceEvaluations.push_back(eval);
    }
    return ifs;
}

void clearScreen() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

int main() {
    vector<Employee> employees;
    Employee emp;
    char option, ch;
    ifstream inFile(fileName, ios::binary);
    ofstream outFile;
    int ID;

    if (inFile) {
        Employee temp;
        while (inFile >> temp) {
            employees.push_back(temp);
        }
        inFile.close();
    }

    do {
        clearScreen();
        cout << "*******Menu********";
        cout << "\nEnter your option";
        cout << "\n1 => Add a new record";
        cout << "\n2 => Search record by employee ID";
        cout << "\n3 => Display all employees";
        cout << "\n4 => Update record of an employee";
        cout << "\n5 => Delete record of a particular employee";
        cout << "\n6 => Add performance evaluation for an employee";
        cout << "\n7 => Display performance evaluations for an employee";
        cout << "\n8 => Exit from the program\n";
        cout << "********************\n";
        cin >> option;
        cin.ignore();

        switch (option) {
        case '1':
            emp.ReadData();
            if (any_of(employees.begin(), employees.end(), [&emp](const Employee& e) { return e.GetID() == emp.GetID(); })) {
                cout << "This ID already exists...Try for another ID";
            } else {
                employees.push_back(emp);
                cout << "New record has been added successfully...";
            }
            break;

        case '2':
            cout << "\nEnter ID of an employee to be searched: ";
            cin >> ID;
            {
                auto it = find_if(employees.begin(), employees.end(), [ID](const Employee& e) { return e.GetID() == ID; });
                if (it != employees.end()) {
                    cout << "\nThe record found....\n";
                    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Job" << setw(8) << "Salary";
                    it->DisplayRecord();
                } else {
                    cout << "\nData not found for employee ID#" << ID;
                }
            }
            break;

        case '3':
            cout << "\nRecords for employees\n";
            cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Job" << setw(8) << "Salary";
            for (const auto& e : employees) {
                e.DisplayRecord();
            }
            cout << "\n" << employees.size() << " records found......";
            break;

        case '4':
            cout << "\nEnter employee ID to be updated: ";
            cin >> ID;
            {
                auto it = find_if(employees.begin(), employees.end(), [ID](const Employee& e) { return e.GetID() == ID; });
                if (it != employees.end()) {
                    cout << "The old record of employee having ID " << ID << " is:";
                    it->DisplayRecord();
                    cout << "\nEnter new record for employee having ID " << ID;
                    it->ReadData();
                    cout << "\nRecord updated successfully...";
                } else {
                    cout << "\nData not found for employee ID#" << ID;
                }
            }
            break;

        case '5':
            cout << "\nEnter employee ID to be deleted: ";
            cin >> ID;
            {
                auto it = remove_if(employees.begin(), employees.end(), [ID](const Employee& e) { return e.GetID() == ID; });
                if (it != employees.end()) {
                    employees.erase(it, employees.end());
                    cout << "\nRecord deleted successfully...";
                } else {
                    cout << "\nData not found for employee ID#" << ID;
                }
            }
            break;

        case '6':
            cout << "\nEnter employee ID to add a performance evaluation: ";
            cin >> ID;
            {
                auto it = find_if(employees.begin(), employees.end(), [ID](const Employee& e) { return e.GetID() == ID; });
                if (it != employees.end()) {
                    it->AddPerformanceEvaluation();
                } else {
                    cout << "\nData not found for employee ID#" << ID;
                }
            }
            break;

        case '7':
            cout << "\nEnter employee ID to display performance evaluations: ";
            cin >> ID;
            {
                auto it = find_if(employees.begin(), employees.end(), [ID](const Employee& e) { return e.GetID() == ID; });
                if (it != employees.end()) {
                    it->DisplayPerformanceEvaluations();
                } else {
                    cout << "\nData not found for employee ID#" << ID;
                }
            }
            break;

        case '8':
            outFile.open(fileName, ios::binary | ios::out | ios::trunc);
            for (const auto& e : employees) {
                outFile << e;
            }
            outFile.close();
            exit(0);

        default:
            cout << "Invalid Option";
        }
        cout << "\nDo you want to continue? (y/n): ";
        cin >> ch;
    } while (ch != 'n');

    return 0;
}
