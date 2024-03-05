#include <iostream>
#include "Polynomial.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "==============================================================================" << std::endl;
    Polynomial polynomial1;

    std::cin >> polynomial1;
    std::cout << polynomial1 << std::endl;

    // polynomial.Print();
    std::cout << "==============================================================================" << std::endl;
    int x_value = 3;
    std::cout << std::format("Result when x = {} is {}", x_value, polynomial1.GetResult(x_value))
              << std::endl;

    // Maker another polynomial
    std::cout << "==============================================================================" << std::endl;
    Polynomial polynomial2;

    std::cin >> polynomial2;
    std::cout << polynomial2 << std::endl;

    // Sum of 2
    std::cout << "==============================================================================" << std::endl;
    Polynomial sum = polynomial1 + polynomial2;
    std::cout << polynomial1
              << "\n+\n"
              << polynomial2
              << "\n=\n"
              << sum << std::endl;

    // Product of 2
    std::cout << "==============================================================================" << std::endl;
    Polynomial product = polynomial1 * polynomial2;
    std::cout << polynomial1
              << "\n*\n"
              << polynomial2
              << "\n=\n"
              << product << std::endl;

    return 0;
}
