#include <iostream>
#include <limits>
#include <string>
#include "payroll.h"

using namespace payroll;

namespace {

    // read input to include spaces
    std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string s;
        // read the entire line, spaces included, and assign value to s
        std::getline(std::cin, s);
        return s;
    }

    // read a number with validation. Template is used to dynamically cast expected type to return value
    template <typename T>
    T readNumber(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            // instantiate variable value of template type <T> deduced from the caller and assign initial value of 0 for given numeric type
            T value{};
            // read the buffer stream character by character until a non-matching type to <T> value is reached.
            // If no matching characters exist from the start, skip the rest of the if conditional block and throw a failbit status
            if (std::cin >> value) {
                // clear the rest of the buffer until a newline character is reached
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            // clear the failbit status
            std::cin.clear();
            // clear the rest of the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
        }
    }

    EvalScore readEvalScore() {
        std::cout << "Evaluation (0=SUPERB, 1=ABOVE_AVERAGE, 2=AVERAGE, 3=BELOW_AVERAGE, 4=UNSATISFACTORY): ";
        int v;
        // similar to readNumber, but in this version if fail condition exists to start, clear the failbit and assign a default value of 2 (AVERAGE)
        if (!(std::cin >> v)) {
            std::cin.clear();
            v = 2;
        }
        // clear the rest of the buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // if the value is not within the valid range of the enum EvalScore, then assign a default value of 2 (AVERAGE)
        if (v < 0 || v > 4) v = 2;
        return static_cast<EvalScore>(v);
    }

    void printMenu() {
        std::cout << "\n *** Payroll System *** \n"
                << "1. Hire Employee\n"
                << "2. Fire Employee (by UID)\n"
                << "3. Give Raise (by UID)\n"
                << "4. Give Raise (by Name)\n"
                << "5. Set Evaluation (by UID)\n"
                << "6. List All Employees\n"
                << "7. Find Employee by UID\n"
                << "8. Find Employees by Name\n"
                << "9. Find Employees by Department\n"
                << "10. Show Total Payroll\n"
                << "0. Exit\n";
    }

} 

int main() {
    EmployeePayroll payroll;

    while (true) {
        printMenu();
        int choice = readNumber<int>("Select option: ");

        if (choice == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1: {
                NewEmployeeArgs a;
                a.firstName  = readLine("First name: ");
                a.lastName   = readLine("Last name: ");
                a.age        = readNumber<int>("Age: ");
                a.department = readLine("Department: ");
                a.supervisor = readLine("Supervisor: ");
                a.position   = readLine("Position: ");
                a.salary     = readNumber<double>("Salary: ");
                payroll.hire(a);
                std::cout << "Hired. Current headcount: " << payroll.size() << "\n";
                break;
            }
            case 2: {
                auto uid = readNumber<std::size_t>("UID to fire: ");
                payroll.fire(uid);
                std::cout << "If found, employee was removed. Headcount: " << payroll.size() << "\n";
                break;
            }
            case 3: {
                auto uid = readNumber<std::size_t>("UID for raise: ");
                double amt = readNumber<double>("Raise amount: ");
                payroll.giveRaise(uid, amt);
                std::cout << "If found, raise applied.\n";
                break;
            }
            case 4: {
                std::string fn = readLine("First name: ");
                std::string ln = readLine("Last name: ");
                double amt = readNumber<double>("Raise amount: ");
                payroll.giveRaise(fn, ln, amt);
                std::cout << "If found, raise applied.\n";
                break;
            }
            case 5: {
                auto uid = readNumber<std::size_t>("UID for evaluation: ");
                EvalScore s = readEvalScore();
                payroll.setEvaluation(uid, s);
                std::cout << "If found, evaluation updated.\n";
                break;
            }
            case 6: {
                payroll.printAllEmployeeInfo();
                break;
            }
            case 7: {
                auto uid = readNumber<std::size_t>("UID to find: ");
                if (auto* e = payroll.findByUid(uid)) {
                    std::cout << *e;
                } else {
                    std::cout << "No employee with UID " << uid << " found.\n";
                }
                break;
            }
            case 8: {
                std::string fn = readLine("First name: ");
                std::string ln = readLine("Last name: ");
                auto list = payroll.findAllByName(fn, ln);
                if (list.empty()) {
                    std::cout << "No matches.\n";
                } else {
                    for (auto* e : list) std::cout << *e;
                }
                break;
            }
            case 9: {
                std::string dept = readLine("Department: ");
                auto list = payroll.findByDepartment(dept);
                if (list.empty()) {
                    std::cout << "No matches.\n";
                } else {
                    for (auto* e : list) std::cout << *e;
                }
                break;
            }
            case 10: {
                std::cout << "Total Payroll: $" << payroll.calculatePayroll() << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
