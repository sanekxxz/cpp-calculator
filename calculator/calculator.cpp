#include "calculator.h"
#include <cmath>
// Реализуйте здесь методы класса.

void Calculator::Set(Number n) {
    num_second_ = n;
}
Number Calculator::GetNumber() const {
    return num_second_;
}
void Calculator::Add(Number n) {
    num_second_ += n;
}
void Calculator::Sub(Number n) {
    num_second_ -= n;
}
void Calculator::Div(Number n) {
    num_second_ /= n;
}
void Calculator::Mul(Number n) {
    num_second_ *= n;
}
void Calculator::Pow(Number n) {
    num_second_ = std::pow(num_second_, n);
}
std::string Calculator::GetNumberRepr() const {
    return std::to_string(num_second_);
}
