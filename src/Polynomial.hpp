#pragma once

#include <iostream>
#include <cmath>
#include <format>

class Polynomial
{
private:
    int m_degree = 0;
    double *m_coefficients;

public:
    Polynomial();
    Polynomial(int degree);
    ~Polynomial();

    void Print() const;
    int GetResult(const int x_value);

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial);
    friend std::istream &operator>>(std::istream &in, Polynomial &polynomial);
};

Polynomial::Polynomial() : m_degree(0), m_coefficients(0) {}

Polynomial::Polynomial(int degree) : m_degree(degree)
{
    // Make a vector or coefficients
    int copyOfDegree = this->m_degree;
    this->m_coefficients = new double[this->m_degree + 1];

    // Assign the Coefficients
    int letterAValue = 97;
    int finalLetter = letterAValue + copyOfDegree + 1;
    for (size_t asciiValue = letterAValue; asciiValue < finalLetter; asciiValue++)
    {
        if (asciiValue == finalLetter - 1)
        {
            break;
        }

        char letterA = static_cast<char>(asciiValue);

        std::cout << std::format(
            "Enter {} as {}x^{}: ",
            letterA,
            letterA,
            copyOfDegree);

        // Assign the value
        std::cin >> this->m_coefficients[copyOfDegree];

        // Decrease the coefficient
        copyOfDegree--;
    }

    // Assign the final coefficient
    std::cout << "Enter last coefficient e: ";
    std::cin >> this->m_coefficients[copyOfDegree];
}

Polynomial::~Polynomial()
{
    delete[] this->m_coefficients;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial)
{
    bool firstTerm = true;
    for (int degree = polynomial.m_degree; degree >= 0; degree--)
    {
        // Skip terms with zero coefficient
        if (polynomial.m_coefficients[degree] == 0)
        {
            continue;
        }

        // Handle sign for all terms except the first
        if (!firstTerm)
        {
            os << (!std::signbit(polynomial.m_coefficients[degree]) ? " + " : " - ");
        }
        firstTerm = false;

        // Print coefficient and term
        if (degree > 0)
        {
            os << std::abs(polynomial.m_coefficients[degree]) << "x^" << degree;
        }
        else
        {
            os << std::abs(polynomial.m_coefficients[degree]);
        }
    }
    return os;
}

std::istream &operator>>(std::istream &in, Polynomial &polynomial)
{
    // Ask to Input a size for the coefficients
    std::cout << "Input the degree of the polynomial: ";
    in >> polynomial.m_degree;

    // Make a vector or coefficients
    int copyOfDegree = polynomial.m_degree;

    delete[] polynomial.m_coefficients; // Deallocate memory of the Pointer
    polynomial.m_coefficients = new double[polynomial.m_degree + 1];

    // Assign the Coefficients
    int letterAValue = 97;
    int finalLetter = letterAValue + copyOfDegree + 1;
    for (size_t asciiValue = letterAValue; asciiValue < finalLetter; asciiValue++)
    {
        if (asciiValue == finalLetter - 1)
        {
            break;
        }

        char letterA = static_cast<char>(asciiValue);

        std::cout << std::format(
            "Enter {} as {}x^{}: ",
            letterA,
            letterA,
            copyOfDegree);

        // Assign the value
        in >> polynomial.m_coefficients[copyOfDegree];

        // Decrease the coefficient
        copyOfDegree--;
    }

    // Assign the final coefficient
    std::cout << "Enter last coefficient e: ";
    in >> polynomial.m_coefficients[copyOfDegree];

    return in;
}

void Polynomial::Print() const
{
    bool firstTerm = true;
    for (int degree = this->m_degree; degree >= 0; degree--)
    {
        // Skip terms with zero coefficient
        if (this->m_coefficients[degree] == 0)
        {
            continue;
        }

        // Handle sign for all terms except the first
        if (!firstTerm)
        {
            std::cout << (!std::signbit(this->m_coefficients[degree]) ? " + " : " - ");
        }
        firstTerm = false;

        // Print coefficient and term
        if (degree > 0)
        {
            std::cout << std::abs(this->m_coefficients[degree]) << "x^" << degree;
        }
        else
        {
            std::cout << std::abs(this->m_coefficients[degree]);
        }
    }
    std::cout << std::endl;
}

int Polynomial::GetResult(const int x_value)
{
    // Result to return
    int result = 0;

    // Make a vector or coefficients
    int copyOfDegree = this->m_degree;

    // Assign the Coefficients
    for (int degree = copyOfDegree; degree >= 0; degree--)
    {
        int coefficient = this->m_coefficients[copyOfDegree];

        result += (coefficient * std::pow(x_value, degree));
    }

    return result;
}