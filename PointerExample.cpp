#include <iostream>

int main() {
    int* ptr = new int;
    *ptr = 10;
    std::cout << "Address of ptr: " << ptr << std::endl;
    std::cout << "Value of ptr: " << *ptr << std::endl;
    std::cout << "--------------------------------" << std::endl;

    float value = 10.5;
    float* ptr2 = &value;
    std::cout << "Address of ptr2: " << ptr2 << std::endl;
    std::cout << "Value of ptr2: " << *ptr2 << std::endl;
    std::cout << "Address of pointer ptr2: " << &ptr2 << std::endl;
    std::cout << "--------------------------------" << std::endl;
   
    *ptr2 = 20.5;
    std::cout << "Updated ptr2 Value: " << *ptr2 << std::endl;
    std::cout << "Updated Value of orignal variable: " << value << std::endl;
    std::cout << "--------------------------------" << std::endl;
   
    float** ptr3 = &ptr2;  // pointers of pointer
    std::cout << "Address of pointer of pointerptr3: " << *ptr3 << std::endl;
    std::cout << "value of ptr3: " << **ptr3 << std::endl;

    delete ptr;
    return 0;
}