#include <iostream>


//need to compile this

struct foo {
    int f;
};

int main() {

    std::cout << "Hello, Multithreading!" << std::endl;

    int* leakData = new int[100];
    leakData[0] = 999;
    std::cout << leakData[0] << std::endl;

    foo* pleaseError = new foo;
    delete pleaseError;
    pleaseError->f = leakData[0];

    return 0;
}