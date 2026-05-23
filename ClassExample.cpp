// g++ -std=c++17 ClassExample.cpp && ./a.out
#include <iostream>
using namespace std;
class Employee {
    public:
        string name;
        int age;
        double salary;
    private:
        string secretcode;

    public:
Employee(string name, int age, double salary, string secretcode) {
    this->name = name;
    this->age = age;
    this->salary = salary;
    this->secretcode = secretcode;
}
void addAge(int age) {
    this->age += age;
}
void addSalary(double salary) {
    this->salary += salary;
}
void printEmployee() {
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Salary: " << salary << endl;
}
};


int main() {
    Employee employee = Employee("Ali Asghar", 30, 50000.0, "123456");
    employee.printEmployee();
    employee.age =50;
    employee.addAge(10);
    employee.addSalary(10000.0);
    // employee.secretcode = "654321";
    employee.printEmployee();
    return 0;
}