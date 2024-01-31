#include <math.h>
#include "complex.h"

double Complex::magnitude() const {
    return sqrt(re_*re_ + im_*im_);
}

bool operator<(const Complex& a, const Complex& b) {
    return a.magnitude() < b.magnitude();
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(re_ + other.re_, im_ + other.im_);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(re_ * other.re_ - im_ * other.im_, re_ * other.im_ + im_ * other.re_);
}

bool Complex::operator==(const Complex& other) const {
    return re_ == other.re_ && im_ == other.im_;
}