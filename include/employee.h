#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <iomanip>

// common namespace to ensure accessibility inside other header files
namespace payroll {

    // alias: cleans up use of string typing without using std namespace
    using string = std::string;
    
    // enum for evaluation scores
    enum EvalScore {
        SUPERB,
        ABOVE_AVERAGE,
        AVERAGE,
        BELOW_AVERAGE,
        UNSATISFACTORY
    };

    // struct for employee attributes: used in initialization of an employee instance 
    struct EmployeeArgs {
        std::size_t uid;
        string firstName;
        string lastName;
        int age;
        string department = "";
        string supervisor = "";
        string position = "";
        double salary = 0.0;
    };

    // employee class
    class Employee {
        // private attributes only accessible to methods inside the class
        private:
            std::size_t uid;
            string fName;
            string lName;
            int age;
            string department;
            string supervisor;
            string position;
            double salary;
            EvalScore evaluation;

        // publicly accessible class methods
        public:
            // constructor
            Employee(const EmployeeArgs& args) // uses the EmployeeArgs struct for cleaner initialization
              : uid(args.uid),
                fName(args.firstName),
                lName(args.lastName),
                age(args.age),
                department(args.department), 
                supervisor(args.supervisor),
                position(args.position),
                salary(args.salary),
                evaluation(AVERAGE)
            {}

            // deconstructor to prevent memory leaks
            ~Employee() = default;

            // Setters
            void setfName(const string& firstName) { fName = firstName; }
            void setlName(const string& lastName) { lName = lastName; }
            void setAge(int empAge) { age = empAge; }
            void setDept(const string& dept) { department = dept; }
            void setSupervisor(const string& sup) { supervisor = sup; }
            void setPosition(const string& pos) { position = pos; }
            void setSalary(double pay) { salary = pay; }            
            void setEval(const EvalScore& score) { evaluation = score; }

            // Getters
            std::size_t getUid() const { return uid; }
            string getfName() const { return fName; } 
            string getlName() const { return lName; } 
            int getAge() const { return age; } 
            string getDepartment() const { return department; } 
            string getSupervisor() const { return supervisor; } 
            string getPosition() const { return position; } 
            double getSalary() const { return salary; }            
            EvalScore getEval() const { return evaluation; }

            // Methods
            // Used when printing to console: checks the current evaluation value and returns the appropriate string
            string evalToString() const {
                switch (evaluation) {
                    case SUPERB: return "SUPERB";
                    case ABOVE_AVERAGE: return "ABOVE_AVERAGE";
                    case AVERAGE: return "AVERAGE";
                    case BELOW_AVERAGE: return "BELOW_AVERAGE";
                    case UNSATISFACTORY: return "UNSATISFACTORY";
                    default: return "UNKNOWN";
                }
            }

            // Increase the salary of employee by a given amount
            void giveRaise(double amount) { salary += amount; }

            // Print out employee information to the console: declaration as friend allows access to private attributes
            friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
    };

    // implemented outside of class to reduce compile time 
    std::ostream& operator<<(std::ostream& os, const Employee& emp){
        os << "\n------------------------\n";
        os << "UID: " << emp.uid << "\n"
            << "First Name: " << emp.fName << "\n"
            << "Last Name: " << emp.lName << "\n"
            << "Age: " << emp.age << "\n"
            << "Department: " << emp.department << "\n"
            << "Supervisor: " << emp.supervisor << "\n"
            << "Position: " << emp.position << "\n"
            << "Salary: $" << std::fixed << std::setprecision(2) << emp.salary << "\n"
            << "Evaluation: " << emp.evalToString() << "\n";
        return os;
    }
}

#endif