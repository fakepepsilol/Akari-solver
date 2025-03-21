cmake_minimum_required(VERSION 3.31)
project(Akari-solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(trivial-solver STATIC src/trivial-solver.cpp)
add_library(level STATIC src/level.cpp)
add_library(https STATIC src/https.cpp)
add_library(js STATIC src/js.cpp)
target_include_directories(trivial-solver PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(level PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(https PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(js PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(main src/main.cpp)
add_executable(tests src/tests.cpp)

target_link_libraries(main PRIVATE
  trivial-solver
  level
  https
  js)
target_link_libraries(tests PRIVATE
  trivial-solver
  level
  https
  js)
