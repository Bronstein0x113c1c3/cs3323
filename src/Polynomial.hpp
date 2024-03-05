#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

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

#endif