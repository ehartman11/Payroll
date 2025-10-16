# PayrollSystem (C++)

A small, modern C++ payroll demo featuring:
- Clean class design (`Employee`, `EmployeePayroll`)
- Pointer ownership + manual memory management (for learning)
- Unique ID assignment via monotonic counter
- Searching (by UID, name, department)
- Raises, evaluations, payroll total
- Menu-driven CLI

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
./payroll

Project Structure
include/
  employee.h
  payroll.h
src/
  main.cpp
CMakeLists.txt
