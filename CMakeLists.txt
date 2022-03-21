cmake_minimum_required(VERSION 3.18)
project(CommonTemplate LANGUAGES CXX VERSION 0.1.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DVERSION_CODE="${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
add_definitions(-DVERSION_NUM=${PROJECT_VERSION_MAJOR}${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH})

add_executable(miscellaneous_test test/miscellaneous_test.cpp)
target_include_directories(miscellaneous_test PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(constexpr_string_test test/constexpr_string_test.cpp)
target_include_directories(constexpr_string_test PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(typename_test test/typename_test.cpp)
target_include_directories(typename_test PRIVATE ${CMAKE_SOURCE_DIR})

