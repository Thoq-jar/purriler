#include <iostream>
#include <string>

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void printPattern(int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    
    std::cout << "Hello, " << name << "!" << std::endl;
    
    for (int i = 1; i <= 5; i++) {
        std::cout << i << "! = " << factorial(i) << std::endl;
    }
    
    std::cout << "\nHere's a pattern for you:\n";
    printPattern(4);
    
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    
    std::cout << "\nSum of multiples of 3 or 5 up to 100: " << sum << std::endl;
    return 0;
}
