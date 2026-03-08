#include <benchmark/benchmark.h>
#include "sort.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

static void BM_SortWithThreshold(benchmark::State& state) {
    // Create the master data set once
    std::vector<double> master_v(10000);
    std::iota(master_v.rbegin(), master_v.rend(), 0);

    size_t threshold = state.range(0);

    for (auto _ : state) {
        // Copy the data for each run
        state.PauseTiming();
        std::vector<double> v = master_v;
        state.ResumeTiming();

        sort(v, threshold);
        benchmark::ClobberMemory(); // Prevent optimizations
    }
}

BENCHMARK(BM_SortWithThreshold)->DenseRange(0, 256, 16);

BENCHMARK_MAIN();