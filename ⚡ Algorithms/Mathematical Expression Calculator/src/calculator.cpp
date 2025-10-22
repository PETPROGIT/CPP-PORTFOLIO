#include "calculator.h"
using namespace std;

// Check if the character is a valid arithmetic operator
constexpr bool IsOperation(const char symbol) noexcept {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'; 
}

// Get operator priority for Shunting Yard
constexpr unsigned short PriorityOperation(const char operation) noexcept {
    if (operation == '(') return 0;
    else if (operation == '+' || operation == '-') return 1;
    return 2;
}

// Execute operation on two top numbers of Nums stack
void DoOperation(stack<double>& Nums, const char operation) {
    if (Nums.size() < 2) {
        throw SyntaxError();
    }
    double top = Nums.top();
    Nums.pop();
    switch (operation) {
        case '+': Nums.top() += top; break;
        case '-': Nums.top() -= top; break;
        case '*': Nums.top() *= top; break;
        case '/': 
            if (top == 0) {
                throw DivisionByZero();
            }
            Nums.top() /= top;
            break;
        default: break;
    }
}

// Main calculation function using Shunting Yard algorithm
double Calculate(const std::string_view& expression) {
    if (expression.length() == 0) {
        throw SyntaxError();
    }

    stack<double> Nums;
    stack<char> Operations;

    for (size_t i = 0; i < expression.length(); ++i) {
        if (expression[i] == ' ') {
            continue;
        }
        else if (isdigit(expression[i]) || expression[i] == '.') { // Number parsing
            bool pointInNum = (expression[i] == '.');
            size_t j = i;
            while (j < expression.length() && 
                (isdigit(expression[j]) || expression[j] == '.'))
            {
                if (expression[j] == '.') {                    
                    if (pointInNum) {
                        throw SyntaxError();
                    }
                    pointInNum = true;
                }
                j++;
            }
            string num_str = string(expression.substr(i, j - i));
            try {
                Nums.push(stod(num_str));
            } catch (const exception&) {
                throw SyntaxError();
            }
            i = j - 1;
        }
        else if (expression[i] == '(') {
            if (i >= 1 && expression[i - 1] == ')') {
                throw SyntaxError();
            }
            Operations.push(expression[i]);
        }
        else if (IsOperation(expression[i])) { // Arithmetic operator
            while (!Operations.empty() &&
                PriorityOperation(expression[i]) <= PriorityOperation(Operations.top()))
            { // Process higher priority operations first
                DoOperation(Nums, Operations.top());
                Operations.pop();
            }
            Operations.push(expression[i]);
        }
        else if (expression[i] == ')') {
            if (Nums.empty()) {
                throw SyntaxError();
            }
            while (!Operations.empty() && Operations.top() != '(') { // Process until matching '('
                DoOperation(Nums, Operations.top());
                Operations.pop();
            }
            if (Operations.empty()) {
                throw SyntaxError();
            }
            Operations.pop(); // Remove '('
        }
        else { // Invalid symbol
            throw SyntaxError();
        }
    }
 
    while (!Operations.empty()) {
        DoOperation(Nums, Operations.top());
        Operations.pop();
    }
    if (Nums.size() != 1) {
        throw SyntaxError();
    }
    return Nums.top();
}