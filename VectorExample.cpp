#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << v[0] << std::endl;
    std::cout << v[1] << std::endl;
    std::cout << v[2] << std::endl;
    std::cout << "Size of the vector: " << v.size() << std::endl;

    std::cout << "--------------Deleting Elements------------------" << std::endl;
    while (!v.empty()) {
        std::cout << v.front() << std::endl;
        v.pop_back();
        std::cout << "--------------------------------" << std::endl;
    }
    std::cout << "Size of the vector: " << v.size() << std::endl;
    v.clear();
    return 0;
}