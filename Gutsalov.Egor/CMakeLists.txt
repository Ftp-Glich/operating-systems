cmake_minimum_required(VERSION 3.15)

project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTING "Enable testing" ON)

add_subdirectory(src)

# if(ENABLE_TESTING)
#     add_subdirectory(tests)
#     enable_testing()
# endif()