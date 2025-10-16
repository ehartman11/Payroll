#ifndef PAYROLL_H
#define PAYROLL_H

#include <iostream>
#include <vector>
#include <string>
#include "employee.h"

// common namespace to ensure accessibility inside other header files
namespace payroll {

    // alias: cleans up use of string typing without using std namespace
    using string = std::string;

    // struct for employee attributes: used in initialization of an employee instance in hire method 
    struct NewEmployeeArgs {
        string firstName;
        string lastName;
        int age;
        string department = "";
        string supervisor = "";
        string position = "";
        double salary = 0.0;
    };

    // employee payrolll class
    class EmployeePayroll{

        // attributes accessible only within the employee payroll class
        private:
            std::vector<Employee*> employees;   // array to store all employees
            std::size_t nextUid = 0;            // stores uid to be used in the creation of the next employee instance 

        // publically accessible methods 
        public:
            // constructor
            EmployeePayroll() = default;

            // deconstructor: ensure destruction of all employee instances to prevent memory leaks
            ~EmployeePayroll() {
                for (Employee* emp : employees) {
                    delete emp;
                }
            }

            // create a new employee instance and append them to the employees array
            void hire(const NewEmployeeArgs& args) {
                EmployeeArgs fullArgs;
                
                fullArgs.uid = nextUid++; // NewEmployeeArgs struct does not have .uid, this is used to assign, then increment, nextUid 
                fullArgs.firstName = args.firstName;
                fullArgs.lastName = args.lastName;
                fullArgs.age = args.age;
                fullArgs.department = args.department;
                fullArgs.supervisor = args.supervisor;
                fullArgs.position = args.position;
                fullArgs.salary = args.salary;

                employees.push_back(new Employee(fullArgs));
            }

            // free the employee instance from the heap and remove its pointer from the employees array
            void fire(std::size_t id) {
                std::size_t index = 0;
                for (Employee* e : employees) {
                    if (e->getUid() == id) {
                        delete e;
                        employees.erase(employees.begin() + index);
                        break;
                    }
                    index++;
                }
            }

            // get the number of employees
            std::size_t size() const { return employees.size(); }

            // add the given amount to the desired employee's salary (using uid)
            void giveRaise(std::size_t id, double amount) {
                for (Employee* e : employees) {
                    if (e->getUid() == id) {
                        e->giveRaise(amount);
                        break;
                    }
                }
            }

            // add the given amount to the desired employee's salary (using employee)
            void giveRaise(const string& firstName, const string& lastName, double amount) {
                for (Employee* e : employees) {
                    if ((e->getfName() == firstName) && e->getlName() == lastName) {
                        e->giveRaise(amount);
                        break;
                    }
                }
            }

            // set the evaluation score of the given employee
            void setEvaluation(std::size_t id, EvalScore score) {
                for (Employee* e : employees) {
                    if (e->getUid() == id) {
                        e->setEval(score);
                        break;
                    }
                }    
            }

            // calculate and return the total of all employees' salaries
            double calculatePayroll() const {
                double total = 0.0;
                for(const Employee* e : employees) {
                    total += e->getSalary();
                }
                return total;
            }

            // print to the console all employees' information 
            void printAllEmployeeInfo() const {
                for(const Employee* e : employees) {
                    std::cout << *e; 
                }
            }

            // find an employee by Uid
            Employee* findByUid(std::size_t id) const {
                for (Employee* e : employees) {
                    if (e->getUid() == id) {
                        return e;
                    }
                }
                return nullptr;
            }

            // find an employee(s) by first and last name
            std::vector<const Employee*> findAllByName(const string& firstName, const string& lastName) const {
                std::vector<const Employee*> foundList;
                for (const Employee* e : employees) {
                    if ((e->getfName() == firstName) && (e->getlName() == lastName)) {
                        foundList.push_back(e);
                    }
                }
                return foundList;
            }

            // find employee(s) by department
            std::vector<const Employee*> findByDepartment(const string& dept) const {
                std::vector<const Employee*> foundList;
                for (const Employee* e : employees) {
                    if (e->getDepartment() == dept) {
                        foundList.push_back(e);
                    }
                }
                return foundList;
            }
    };

}

#endif