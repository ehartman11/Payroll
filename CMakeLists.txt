cmake_minimum_required(VERSION 3.10)
project(PayrollSystem CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(payroll
    src/main.cpp
)

# If you later split implementations:
# add_library(payrolllib
#     src/employee.cpp
#     src/payroll.cpp
# )
# target_link_libraries(payroll payrolllib)

Build & run:

mkdir build && cd build
cmake ..
cmake --build .
./payroll
