#include "iostream"
#include "vector"
#include "iomanip"
#include "cmath"
#include "calculator.h"

using namespace std;

struct TestCase {
    string expression;
    double expected;
    bool should_throw = false;
    string exception_type = "";
};

void RunTests() {
    vector<TestCase> tests = {
        {"2 + 2", 4.0},
        {"5 - 3", 2.0},
        {"3 * 4", 12.0},
        {"8 / 2", 4.0},
        {"2 + 3 * 4", 14.0},
        {"(2 + 3) * 4", 20.0},
        {"10 - 2 - 3", 5.0},
        {"2 * 3 + 4 * 5", 26.0},
        {"2 * (3 + 4) * 5", 70.0},
        {"2.5 + 3.5", 6.0},
        {"3.14 * 2", 6.28},
        {"10.5 / 2", 5.25},
        {"0.1 + 0.2", 0.3},
        {"1.5 * 2.5", 3.75},
        {"(1 + 2) * (3 + 4)", 21.0},
        {"10 / (2 + 3)", 2.0},
        {"3 + 4 * 2 / (1 - 5)", 1.0},
        {"(5 + 3) * (10 - 4) / 2", 24.0},
        {"2 + 3 * 4 - 5 / 1", 9.0},
        {"(2 + 3) * (4 - 1) / (6 - 3)", 5.0},
        {"((2 + 3) * 4)", 20.0},
        {"(1 + (2 * (3 + 4)))", 15.0},
        {"((1 + 2) * (3 + 4)) / 5", 4.2},
        {"(1 + (2 * (3 + (4 - 1))))", 13.0},
        {"0 + 5", 5.0},
        {"5 * 0", 0.0},
        {"1 * 1 * 1 * 5", 5.0},
        {"0 * 100 + 5", 5.0},
        {"5 + 0 * 100", 5.0},
        {"1000 + 2000", 3000.0},
        {"999 * 2", 1998.0},
        {"10000 / 100", 100.0},
        {"1 + 2 + 3 + 4 + 5", 15.0},
        {"1 * 2 * 3 * 4 * 5", 120.0},
        {"(1 + 2) + (3 + 4) + (5 + 6)", 21.0},
        {"10 - 1 - 2 - 3 - 4", 0.0},
        {"3 * 4 + 5 * 6 - 7 * 2", 28.0},
        {"(3 + 4) * (5 - 2) + 10 / 2", 26.0},
        {"100 - 50 * 2 + 25 / 5", 5.0},
        {"2.5 * 4 + 1.5 * 2 - 3.5", 9.5},
        {"1 / 2", 0.5},
        {"0 / 5", 0.0},
        {"2.5 / 0.5", 5.0},
        {"100 / 3", 100.0/3},
        {"0.5 * 0.5", 0.25},
        {"1.25 + 2.75", 4.0},
        {"10.1 - 5.1", 5.0},
        {"2.2 * 5", 11.0},
        {"2 + 3 * 4 - 5 / 2 + 1", 12.5},
        {"(2 + 3) * (4 - 1) / 3 + 2", 7.0},
        {"10 - 2 * 3 + 4 / 2", 6.0},
        {"5 * (3 + 2) - 4 / 2 + 1", 24.0},
        {"((((5 + 3))))", 8.0},
        {"(1 + (2 + (3 + (4 + 5))))", 15.0},
        {"(2 * (3 + (4 * (1 + 1))))", 22.0},
        {"((10 - 2) * (3 + 1)) / ((5 - 1) * 2)", 4.0},

        // Division by zero errors
        {"5 / 0", 0.0, true, "DivisionByZero"},
        {"1 / (2 - 2)", 0.0, true, "DivisionByZero"},
        {"(5 + 3) / (4 - 4)", 0.0, true, "DivisionByZero"},
        {"0 / 0", 0.0, true, "DivisionByZero"},
        {"1 / (1 - 1)", 0.0, true, "DivisionByZero"},

        // Syntax errors
        {"2 + ", 0.0, true, "SyntaxError"},
        {"(2 + 3", 0.0, true, "SyntaxError"},
        {"2 + 3)", 0.0, true, "SyntaxError"},
        {"2 ++ 3", 0.0, true, "SyntaxError"},
        {"2..3 + 1", 0.0, true, "SyntaxError"},
        {"2 + a", 0.0, true, "SyntaxError"},
        {"", 0.0, true, "SyntaxError"},
        {"()", 0.0, true, "SyntaxError"},
        {"( )", 0.0, true, "SyntaxError"},
        {"5 + * 3", 0.0, true, "SyntaxError"},
        {"* 5 + 3", 0.0, true, "SyntaxError"},
        {"5 5 + 3", 0.0, true, "SyntaxError"},
        {"5 + 3 3", 0.0, true, "SyntaxError"},
        {".5 + 3", 0.0, true, "SyntaxError"},

        {"5. + 3", 8},
        {"  2  +  3  ", 5.0},
        {"2+3", 5.0},
        {" ( 2 + 3 ) * 4 ", 20.0},
        {"2+3*4", 14.0},
        {"(2+3)*4", 20.0},
        {"  10   -   5   *   2   ", 0.0},
        {"((15 - 3) * 2 + 8) / 4 - 1", 7.0},
        {"3.5 * (2 + 4.5) - 1.25 / 0.5", 20.25},
        {"(100 - 25 * 3) / 5 + 10 * 2", 25.0},
        {"2 * (3 + 4 * (5 - 1)) / (2 + 3)", 7.6},
        {"1", 1.0},
        {"(5)", 5.0},
        {"((((10))))", 10.0},
        {"0", 0.0},
        {"15 / 3 * 4 + 2 - 1", 21.0},
        {"(8 + 2) * (7 - 3) / 4", 10.0},
        {"100 / 10 / 2 * 4 + 3", 23.0},
        {"(5 * 6) + (8 / 2) - (3 * 4)", 22.0},
        {"2.25 * 4 + 3.75 / 1.5", 11.5},
        {"(12 + 8) * (15 - 5) / (4 * 2)", 25.0},
        {"( 1 + ( 2 * ( 3 + ( 4 - ( 5 * ( 6 / ( 7 + ( 8 - ( 9 * 2 ) ) ) ) ) ) ) ) ) - ( ( 10 * 3 ) + ( 5 - ( 8 / ( 2 + 2 ) ) ) )", 2},
        {"(1000 / 100) * (50 / 5) + 25", 125.0},
        {"0.125 * 8 + 0.25 * 4", 2.0},
        {"(3 + 7) * (2 + 8) / (5 + 5)", 10.0}
    };

    int total_tests = tests.size();
    int passed = 0;
    int failed = 0;

    cout << "Running Tests\n";
    cout << "=======================\n\n";

    for (size_t i = 0; i < tests.size(); ++i) {
        const auto& test = tests[i];
        cout << "TEST " << i + 1 << ": ";
        
        bool test_passed = false;
        string result_message;

        try {
            double result = Calculate(test.expression);
            
            if (test.should_throw) {
                result_message = "FAILED - Expected exception but got result: " + to_string(result);
            } else {
                const double epsilon = 1e-10;
                if (fabs(result - test.expected) < epsilon) {
                    test_passed = true;
                    result_message = "PASSED";
                } else {
                    result_message = "FAILED - Expected " + to_string(test.expected) + 
                                   " but got " + to_string(result);
                }
            }
        }
        catch (const DivisionByZero& e) {
            if (test.should_throw && test.exception_type == "DivisionByZero") {
                test_passed = true;
                result_message = "PASSED";
            } else if (test.should_throw) {
                result_message = "FAILED - Got DivisionByZero but expected " + test.exception_type;
            } else {
                result_message = "FAILED - Unexpected DivisionByZero: " + string(e.what());
            }
        }
        catch (const SyntaxError& e) {
            if (test.should_throw && test.exception_type == "SyntaxError") {
                test_passed = true;
                result_message = "PASSED";
            } else if (test.should_throw) {
                result_message = "FAILED - Got SyntaxError but expected " + test.exception_type;
            } else {
                result_message = "FAILED - Unexpected SyntaxError: " + string(e.what());
            }
        }
        catch (const exception& e) {
            result_message = "FAILED - Unexpected exception: " + string(e.what());
        }
        catch (...) {
            result_message = "FAILED - Unknown exception";
        }

        if (test_passed) {
            passed++;
            cout << "PASSED";
        } else {
            failed++;
            cout << "FAILED";
        }

        cout << " " << test.expression;
        
        if (!test_passed) {
            cout << " " << result_message;
        }
        cout << "\n";
    }
    cout << "=======================\n";
    cout << "\nRESULTS\n";
    cout << "TOTAL TESTS: " << total_tests << "\n";
    cout << "PASSED: " << passed << "\n";
    cout << "FAILED: " << failed << "\n";
}

int main() {
    RunTests();
    return 0;
}