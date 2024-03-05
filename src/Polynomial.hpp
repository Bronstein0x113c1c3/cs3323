#pragma once

#include <iostream>
#include <cmath>
#include <format>

class Polynomial
{
private:
    int m_degree = 0;
    double *m_coefficients = nullptr;

public:
    Polynomial();
    Polynomial(int degree);
    ~Polynomial();

    void Print() const;
    int GetResult(const int x_value);

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial);
    friend std::istream &operator>>(std::istream &in, Polynomial &polynomial);

    friend Polynomial &operator+(const Polynomial &polynomial1, const Polynomial &polynomial2);
    friend Polynomial &operator*(const Polynomial &polynomial1, const Polynomial &polynomial2);
};

Polynomial::Polynomial() : m_degree(0), m_coefficients(nullptr) {}

Polynomial::Polynomial(int degree) : m_degree(degree)
{
    // Make a vector or coefficients
    int copyOfDegree = this->m_degree;
    this->m_coefficients = new double[this->m_degree + 1];

    // Assign the Coefficients
    int letterAValue = 97;
    int finalLetter = letterAValue + copyOfDegree;
    for (size_t asciiValue = letterAValue; asciiValue < finalLetter; asciiValue++)
    {
        if (asciiValue == finalLetter)
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
    std::cout << std::format(
        "Enter coefficient {}: ",
        static_cast<char>(finalLetter));

    std::cin >> this->m_coefficients[copyOfDegree];
}

Polynomial::~Polynomial()
{
    delete[] this->m_coefficients;
    this->m_coefficients = nullptr;
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

        // Print the firstTerm if with minus sign
        if (degree == polynomial.m_degree)
        {
            os << polynomial.m_coefficients[degree] << "x^" << degree;
        }
        else if (degree > 0) // Print coefficient and term
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
    int finalLetter = letterAValue + copyOfDegree;
    for (size_t asciiValue = letterAValue; asciiValue < finalLetter; asciiValue++)
    {
        if (asciiValue == finalLetter)
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
    std::cout << std::format(
        "Enter coefficient {}: ",
        static_cast<char>(finalLetter));

    in >> polynomial.m_coefficients[copyOfDegree];

    return in;
}

Polynomial &operator+(const Polynomial &polynomial1, const Polynomial &polynomial2)
{
    Polynomial *result_polynomial = new Polynomial();

    // Make A variable to track the small polynomial.degree will use
    int smaller_PolynomialDegree = -1;
    if (polynomial1.m_degree > polynomial2.m_degree)
    {
        smaller_PolynomialDegree = polynomial2.m_degree;
        result_polynomial->m_degree = polynomial1.m_degree;
    }
    else if (polynomial1.m_degree < polynomial2.m_degree)
    {
        smaller_PolynomialDegree = polynomial1.m_degree;
        result_polynomial->m_degree = polynomial2.m_degree;
    }
    else // If equal
    {
        result_polynomial->m_degree = polynomial1.m_degree;
    }

    // Make a coefficient List for the new one
    result_polynomial->m_coefficients = new double[result_polynomial->m_degree];

    // Time to add 2 Polynomials
    for (size_t degree = 0; degree <= result_polynomial->m_degree; degree++)
    {
        // If 2 polynomial the degree != the same
        if (degree > smaller_PolynomialDegree)
        {
            if (smaller_PolynomialDegree == polynomial1.m_degree)
            {
                result_polynomial->m_coefficients[degree] = polynomial2.m_coefficients[degree];
            }
            else // then smaller_PolynomialDegree == polynomial2.m_degree
            {
                result_polynomial->m_coefficients[degree] = polynomial1.m_coefficients[degree];
            }

            continue;
        }

        result_polynomial->m_coefficients[degree] = polynomial1.m_coefficients[degree] + polynomial2.m_coefficients[degree];
    }

    return *result_polynomial;
}

Polynomial &operator*(const Polynomial &polynomial1, const Polynomial &polynomial2)
{
    // Return Value
    Polynomial *result_polynomial = new Polynomial();

    // Assign the degree
    size_t result_PolynomialDegree = polynomial1.m_degree + polynomial2.m_degree;
    result_polynomial->m_degree = result_PolynomialDegree;

    // Make a coefficient List for the new one
    result_polynomial->m_coefficients = new double[result_PolynomialDegree];

    // Initialize coefficients to zero
    for (size_t i = 0; i < result_PolynomialDegree; i++)
    {
        result_polynomial->m_coefficients[i] = 0.0;
    }

    // Multiply coefficients
    for (size_t indexPoly1 = 0; indexPoly1 <= polynomial1.m_degree; indexPoly1++)
    {
        for (size_t indexPoly2 = 0; indexPoly2 <= polynomial2.m_degree; indexPoly2++)
        {
            result_polynomial->m_coefficients[indexPoly1 + indexPoly2] += (polynomial1.m_coefficients[indexPoly1] * polynomial2.m_coefficients[indexPoly2]);
        }
    }

    return *result_polynomial;
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

        // Print the firstTerm if with minus sign
        if (degree == this->m_degree)
        {
            std::cout << this->m_coefficients[degree] << "x^" << degree;
        }
        else if (degree > 0) // Print coefficient and term
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