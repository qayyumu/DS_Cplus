// g++ -std=c++17 StructExample.cpp && ./a.out
#include <iostream>
using namespace std;

struct Employee {
    string name;
    int age;
    double salary;
};

void printEmployee(Employee employee) {
    std::cout << "Name: " << employee.name << std::endl;
    std::cout << "Age: " << employee.age << std::endl;
    std::cout << "Salary: " << employee.salary << std::endl;
}

int main() {
    Employee employee = {"Ali Khan", 30, 50000.0};
    printEmployee(employee);

    std::cout << "\n\nPointer Example:" << std::endl;

    return 0;
}