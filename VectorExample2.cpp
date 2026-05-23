#include <iostream>
#include <vector>

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
    std::vector<Employee> v;
    v.push_back({"Ali", 30, 50000.0});
    v.push_back({"Aslam", 40, 60000.0});
    v.push_back({"Ahmed", 50, 70000.0});

    while (!v.empty()) {
        Employee employee = v.front();
        printEmployee(employee);
        std::cout << "--------------------------------" << std::endl;
        v.pop_back();
    }

    return 0;
}