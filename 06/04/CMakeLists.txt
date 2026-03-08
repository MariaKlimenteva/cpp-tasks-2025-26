cmake_minimum_required(VERSION 3.28)
project(EducationExamples)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.85 REQUIRED COMPONENTS system filesystem)
find_package(TBB REQUIRED)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# Google Test configuration
enable_testing()

# Example executable
add_executable(example_app main.cpp)
target_link_libraries(example_app PRIVATE 
    Boost::system 
    Boost::filesystem 
    TBB::tbb
)

# Example test
add_executable(unit_tests tests.cpp)
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)
add_test(NAME MyTest COMMAND unit_tests)

# Example benchmark
add_executable(benchmarks bench.cpp)
target_link_libraries(benchmarks PRIVATE benchmark::benchmark)