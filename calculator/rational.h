#pragma once

#include <numeric>
#include <iostream>

class Rational{
public:
    Rational()=default;
    Rational(int num, int den) : numerator_(num), denominator_(den) {
        Reduction();
    };
    Rational(int num) : numerator_(num) {};
    Rational(const Rational& r) : numerator_(r.numerator_), denominator_(r.denominator_) {};

    Rational Inv() const{
        return Rational(denominator_, numerator_);
    }

    int GetNumerator() const{
        return numerator_;
    }

    int GetDenominator() const{
        return denominator_;
    }

    Rational operator*=(const Rational& r){
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational operator/=(const Rational& r){
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }

    Rational operator-=(const Rational& r){
        numerator_ = numerator_*r.denominator_ - denominator_*r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational operator+=(const Rational& r){
        numerator_ = numerator_*r.denominator_ + denominator_*r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator=(const Rational& r){
        numerator_ = r.numerator_;
        denominator_ = r.denominator_;
        return *this;
    }

    bool operator==(const Rational& r) const{
        int num_1 = numerator_ * r.denominator_;
        int num_2 = denominator_ * r.numerator_;
        return num_1 == num_2;
    }

    auto operator<=>(const Rational& r) const{
        int num_1 = numerator_ * r.denominator_;
        int num_2 = denominator_ * r.numerator_;
        return num_1 <=> num_2;
    }

    Rational operator-() const{
        int num = -numerator_;
        return Rational(num, denominator_);
    }

    Rational operator+() const{
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational &r);
    Rational operator*(const Rational& r2) const{
        return Rational(numerator_ * r2.numerator_, denominator_ * r2.denominator_);
    }
    Rational operator/(const Rational& r2) const {
        return Rational(numerator_ / r2.numerator_, denominator_ / r2.denominator_);
    }
    Rational operator+(const Rational& r2) const {
        return Rational(numerator_ + r2.numerator_, denominator_ + r2.denominator_);
    }
    Rational operator-(const Rational& r2){
        return Rational(numerator_ - r2.numerator_, denominator_ - r2.denominator_);
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r){
    if(r.denominator_ == 1){
        os << r.numerator_;
        return os;
    }
    if(r.numerator_ % r.denominator_ == 0){
        os << r.numerator_ / r.denominator_;
        return os;
    }
    os << r.numerator_ << " / " << r.denominator_;
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational &r){
    int num, den;
    char op;
    is >> num;

    if(is.fail()){
        is.setstate(std::ios::failbit);
        return is;
    }

    if (is.peek() == '\n' || is.peek() == EOF) {
        r.numerator_ = num;
        r.denominator_ = 1;
        return is;
    }

    is >> op;

    if(is.fail()){
        is.clear();
        r.numerator_ = num;
        r.denominator_ = 1;
        return is;
    }

    if(op != '/'){
        is.unget();
        r.numerator_ = num;
        r.denominator_ = 1;
        return is;
    }

    is >> den;

    if(is.fail() || den == 0){
        is.setstate(std::ios::failbit);
        return is;
    }

    r.numerator_=num;
    r.denominator_=den;
    return is;
}
