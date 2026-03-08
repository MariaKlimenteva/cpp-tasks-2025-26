add_executable(07.05_benchmark 07.05.cpp)

find_package(benchmark CONFIG REQUIRED)
target_link_libraries(07.05_benchmark PRIVATE benchmark::benchmark_main)