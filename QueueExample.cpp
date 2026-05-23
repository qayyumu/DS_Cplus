#include <iostream>
#include <queue>

struct Employee {
    std::string name;
    int age;
    double salary;
};

void printEmployee(Employee employee) {
    std::cout << "Name: " << employee.name << std::endl;
    std::cout << "Age: " << employee.age << std::endl;
    std::cout << "Salary: " << employee.salary << std::endl;
}

int main() {
    std::queue<Employee> q;
    q.push({"Ali", 30, 50000.0});
    q.push({"Aslam", 40, 60000.0});
    q.push({"Ahmed", 50, 70000.0});
    while (!q.empty()) {
        Employee employee = q.front();
        printEmployee(employee);
        std::cout << "--------------------------------" << std::endl;
        q.pop();
    }
    return 0;
}