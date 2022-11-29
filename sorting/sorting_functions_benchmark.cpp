#include "sorting_functions.hpp"
#include "benchmark/benchmark.h"
#include <algorithm>
#include <numeric>
#include <vector>

#define REPEAT2(X) X X
#define REPEAT4(X) REPEAT2(X) REPEAT2(X)
#define REPEAT8(X) REPEAT4(X) REPEAT4(X)
#define REPEAT16(X) REPEAT8(X) REPEAT8(X)
#define REPEAT32(X) REPEAT16(X) REPEAT16(X)
#define REPEAT64(X) REPEAT32(X) REPEAT32(X)
#define REPEAT128(X) REPEAT64(X) REPEAT64(X)
#define REPEAT(X) REPEAT128(X) REPEAT128(X)

constexpr auto repetitions = 256;

static void BM_NoSort(benchmark::State& state)
{
    auto array_size = state.range(0);
    auto reference_vector = std::vector<int>(array_size*repetitions);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    std::random_shuffle(reference_vector.begin(), reference_vector.end());
    for (auto _ : state)
    {
        auto copy = reference_vector;
        auto current_start = copy.begin();
        auto current_end = current_start + array_size;
        REPEAT(
        {
            benchmark::DoNotOptimize(current_start += array_size);
            benchmark::DoNotOptimize(current_end += array_size);
            benchmark::DoNotOptimize(copy);
        })
    }
    state.SetItemsProcessed(state.iterations()*repetitions*array_size);
}

static void BM_StdSort(benchmark::State& state)
{
    auto array_size = state.range(0);
    auto reference_vector = std::vector<int>(array_size*repetitions);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    std::random_shuffle(reference_vector.begin(), reference_vector.end());
    for (auto _ : state)
    {
        auto copy = reference_vector;
        auto current_start = copy.begin();
        auto current_end = current_start + array_size;
        REPEAT(
        {
            std::sort(current_start, current_end);
            current_start += array_size;
            current_end += array_size;
            benchmark::DoNotOptimize(copy);
        })
    }
    state.SetItemsProcessed(state.iterations()*repetitions*array_size);
}

static void BM_QuickSort(benchmark::State& state)
{
    auto array_size = state.range(0);
    auto reference_vector = std::vector<int>(array_size*repetitions);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    std::random_shuffle(reference_vector.begin(), reference_vector.end());
    for (auto _ : state)
    {
        auto copy = reference_vector;
        auto current_start = copy.begin();
        auto current_end = current_start + array_size;
        REPEAT(
        {
            quick_sort(current_start, current_end);
            current_start += array_size;
            current_end += array_size;
            benchmark::DoNotOptimize(copy);
        })
    }
    state.SetItemsProcessed(state.iterations()*repetitions*array_size);
}

static void BM_InsertionSort(benchmark::State& state)
{
    auto array_size = state.range(0);
    auto reference_vector = std::vector<int>(array_size*repetitions);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    std::random_shuffle(reference_vector.begin(), reference_vector.end());
    for (auto _ : state)
    {
        auto copy = reference_vector;
        auto current_start = copy.begin();
        auto current_end = current_start + array_size;
        REPEAT(
        {
            insertion_sort(current_start, current_end);
            current_start += array_size;
            current_end += array_size;
            benchmark::DoNotOptimize(copy);
        })
    }
    state.SetItemsProcessed(state.iterations()*repetitions*array_size);
}

static void BM_BubbleSort(benchmark::State& state)
{
    auto array_size = state.range(0);
    auto reference_vector = std::vector<int>(array_size*repetitions);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    std::random_shuffle(reference_vector.begin(), reference_vector.end());
    for (auto _ : state)
    {
        auto copy = reference_vector;
        auto current_start = copy.begin();
        auto current_end = current_start + array_size;
        REPEAT(
        {
            bubble_sort(current_start, current_end);
            current_start += array_size;
            current_end += array_size;
            benchmark::DoNotOptimize(copy);
        })
    }
    state.SetItemsProcessed(state.iterations()*repetitions*array_size);
}

//BENCHMARK(BM_NoSort)->RangeMultiplier(2)->Range(1 << 0, 1 << 10);
//BENCHMARK(BM_StdSort)->RangeMultiplier(2)->Range(1 << 0, 1 << 10);
//BENCHMARK(BM_QuickSort)->RangeMultiplier(2)->Range(1 << 0, 1 << 10);
//BENCHMARK(BM_InsertionSort)->RangeMultiplier(2)->Range(1 << 0, 1 << 10);
//BENCHMARK(BM_BubbleSort)->RangeMultiplier(2)->Range(1 << 0, 1 << 10);
//BENCHMARK(BM_NoSort)->Arg(128)->Iterations(1000000);
//BENCHMARK(BM_StdSort)->Arg(100)->Iterations(1000000);
//BENCHMARK(BM_QuickSort)->Arg(100)->Iterations(1000000);
BENCHMARK(BM_InsertionSort)->Arg(100)->Iterations(1000000);
//BENCHMARK(BM_BubbleSort)->Arg(128)->Iterations(1000000);

BENCHMARK_MAIN();