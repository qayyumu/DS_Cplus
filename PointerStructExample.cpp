#include <iostream>
using namespace std;

struct Employee {
    string name;
    int age;
    double salary;

    Employee(string name, int age, double salary) {
        this->name = name;
        this->age = age;
        this->salary = salary;
    }

    void printEmployee(Employee* employee) {
        std::cout << "Name: " << employee->name << std::endl;
        std::cout << "Age: " << employee->age << std::endl;
        std::cout << "Salary: " << employee->salary << std::endl;
    }

};
int main() {


    Employee* employeePtr = new Employee("Ali", 30, 50000.0);
    employeePtr->printEmployee(employeePtr);
    std::cout << "--------------------------------" << std::endl;

    return 0;
}