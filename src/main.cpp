#include <iostream>
#include "Polynomial.hpp"

int main(int argc, char const *argv[])
{
    Polynomial polynomial;

    std::cin >> polynomial;
    std::cout << polynomial << std::endl;

    // polynomial.Print();
    int x_value = 3;
    std::cout << std::format("Result when x = {} is {}", x_value, polynomial.GetResult(x_value))
              << std::endl;

    return 0;
}
