#pragma once

#include <string>

using Number = double;

// Реализуйте здесь класс Calculator.
class Calculator {
public:
    void Set(Number n);
    Number GetNumber() const;
    void Add(Number n);
    void Sub(Number n);
    void Div(Number n);
    void Mul(Number n);
    void Pow(Number n);
    std::string GetNumberRepr() const;
private:
    Number num_second_ = 0;
};
