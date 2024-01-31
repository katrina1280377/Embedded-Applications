#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y) : re_(x), im_(y) {}
    Complex(double a) : re_(a), im_(0) {};

    double magnitude() const;
    
    // New methods for Homework 4
    double re() const { return re_; }
    double im() const { return im_; }
    Complex conjugate() const { return Complex(re_, -im_); }

    Complex operator+(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    bool operator==(const Complex& other) const;
    
    private:
    double re_, im_;
}; 

bool operator<(const Complex& a, const Complex& b);

#endif