#include "calculator.h"
#include <iostream>
#include <cmath>

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}


bool RunCalculatorCycle() {
    Number Number, Number_first, Number_save;
    bool number_save_bool = false;
    if (!(ReadNumber(Number))) {
        return false;
    }
    else
    {
        std::string symbol;
        do
        {
            std::cin >> symbol;
            if (symbol == "q") {
                break;
            }
            else if (symbol == "+") {
                if (ReadNumber(Number_first)) {
                    Number += Number_first;
                }
                else
                {
                    break;
                }
            }
            else if (symbol == "*") {
                if (ReadNumber(Number_first)) {
                    Number *= Number_first;
                }
                else
                {
                    break;
                }

            }
            else if (symbol == "-") {
                if (ReadNumber(Number_first)) {
                    Number -= Number_first;
                }
                else
                {
                    break;
                }

            }
            else if (symbol == "/") {
                if (ReadNumber(Number_first)) {
                    Number /= Number_first;
                }
                else
                {
                    break;
                }

            }
            else if (symbol == "**") {
                if (ReadNumber(Number_first)) {
                    Number = std::pow(Number, Number_first);
                }
                else
                {
                    break;
                }

            }
            else if (symbol == ":") {
                if (ReadNumber(Number_first)) {
                    Number = Number_first;
                }
                else
                {
                    break;
                }
            }
            else if (symbol == "s") {
                Number_save = Number;
                number_save_bool = true;
            }
            else if (symbol == "l") {
                if (number_save_bool) {
                    Number = Number_save;
                }
                else
                {
                    std::cerr << "Error: Memory is empty" << std::endl;
                    break;
                }
            }
            else if (symbol == "c") {
                Number = 0;
            }
            else if (symbol == "=") {
                std::cout << Number << std::endl;
            }
            else
            {
                std::cerr << "Error: Unknown token " << symbol << std::endl;
                break;
            }
        } while (symbol != "q");
    }
    return 0;
}