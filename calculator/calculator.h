#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"
#include <QString>

using Error = std::string;

template <typename Number>
class Calculator{
public:
    void Set(Number n){
        cur_ = n;
    }

    Number GetNumber() const{
        return cur_;
    }

    std::optional<Error> Add(Number n){
        cur_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number n){
        cur_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(Number n){
        if constexpr(std::is_integral_v<Number> || std::is_same_v<Number, Rational>){
            if(n == 0){
                return Error("Division by zero");
            }
        }
        cur_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number n){
        cur_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n){
        if(cur_ == 0 && n == 0){
            return Error("Zero power to zero");
        }
        if constexpr(std::is_same_v<Number, Rational>){
            if(n.GetDenominator() != 1){
                return Error("Fractional power is not supported");
            }
            cur_ = ::Pow(cur_, n);
        }
        if constexpr (std::is_integral_v<Number>){
            if(n < 0){
                return Error("Integer negative power");
            }
            cur_ = IntegerPow(cur_, n);
        }
        if constexpr (!std::is_same_v<Number, Rational> && !std::is_integral_v<Number>) {
            cur_ = std::pow(cur_, n);
        }
        return std::nullopt;
    }

    void Save(){
        memory_ = cur_;
    }

    void Load(){
        if(memory_.has_value()){
            cur_ = *memory_;
        }
    }

    bool GetHasMem(){
        return memory_.has_value();
    }

private:
    Number cur_ = 0;
    std::optional<Number> memory_;
};
