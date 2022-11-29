#include "benchmark/benchmark.h"
#include <algorithm>
#include <array>
#include <list>
#include <numeric>
#include <utility>
#include <vector>

#define REPEAT2(X) X X
#define REPEAT4(X) REPEAT2(X) REPEAT2(X)
#define REPEAT8(X) REPEAT4(X) REPEAT4(X)
#define REPEAT16(X) REPEAT8(X) REPEAT8(X)
#define REPEAT32(X) REPEAT16(X) REPEAT16(X)
#define REPEAT(X) REPEAT32(X) REPEAT32(X)

constexpr auto repetitions = 64;

constexpr auto max_array_bytes = 1 << 22;
constexpr auto test_factor = 64;

template <int NumBytes, template<typename> typename Container>
static void BM_insert_in_sorted_order(benchmark::State& state)
{
    constexpr auto num_ints = NumBytes / sizeof(int);
    using DataType = std::array<int, num_ints>;
    auto array_bytes = state.range(0);
    auto array_size = array_bytes / sizeof(DataType);
    auto max_array_size = max_array_bytes / sizeof(DataType);
    auto test_size = max_array_size*test_factor;
    auto reference_vector = std::vector<int>(test_size);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    std::random_shuffle(reference_vector.begin(), reference_vector.end());
    auto input_vector = std::vector<std::pair<int, DataType>>(test_size);
    for (auto i = 0; i < test_size; ++i)
    {
        input_vector[i].first = i / array_size;
        input_vector[i].second[0] = reference_vector[i];
    }
    auto n_output_containers = test_size / array_size;
    auto output_containers = std::vector<Container<DataType>>(n_output_containers);
    for (auto _ : state)
    {
        for (auto& input_pair : input_vector)
        {
            auto& current_vector = output_containers[input_pair.first];
            auto current_value = input_pair.second;
            auto it = current_vector.begin();
            for (; it != current_vector.end(); ++it)
            {
                if (current_value[0] < (*it)[0]) { break; }
            }
            benchmark::DoNotOptimize(current_vector.insert(it, current_value));
        }
    }
    state.SetItemsProcessed(state.iterations()*test_size);
}

//template <int NumInts>
//static void BM_vector_insert_in_sorted_order(benchmark::State& state)
//{
//    using DataType = std::array<int, NumInts>;
//    auto array_bytes = state.range(0);
//    auto array_size = array_bytes / sizeof(DataType);
//    auto max_array_size = max_array_bytes / sizeof(DataType);
//    auto test_size = max_array_size*test_factor;
//    auto reference_vector = std::vector<int>(test_size);
//    std::iota(reference_vector.begin(), reference_vector.end(), 0);
//    std::random_shuffle(reference_vector.begin(), reference_vector.end());
//    auto input_vector = std::vector<std::pair<int, DataType>>(test_size);
//    for (auto i = 0; i < test_size; ++i)
//    {
//        input_vector[i].first = i / array_size;
//        input_vector[i].second[0] = reference_vector[i];
//    }
//    auto n_output_vectors = test_size / array_size;
//    auto output_vectors = std::vector<std::vector<DataType>>(n_output_vectors);
//    for (auto _ : state)
//    {
//        for (auto& input_pair : input_vector)
//        {
//            auto& current_vector = output_vectors[input_pair.first];
//            auto current_value = input_pair.second;
//            auto it = current_vector.begin();
//            for (; it != current_vector.end(); ++it)
//            {
//                if (current_value[0] < (*it)[0]) { break; }
//            }
//            benchmark::DoNotOptimize(current_vector.insert(it, current_value));
//        }
//    }
//    state.SetItemsProcessed(state.iterations()*test_size);
//}
//
//template <int NumInts>
//static void BM_list_insert_in_sorted_order(benchmark::State& state)
//{
//    using DataType = std::array<int, NumInts>;
//    auto array_bytes = state.range(0);
//    auto array_size = array_bytes / sizeof(DataType);
//    auto max_array_size = max_array_bytes / sizeof(DataType);
//    auto test_size = max_array_size*test_factor;
//    auto reference_vector = std::vector<int>(test_size);
//    std::iota(reference_vector.begin(), reference_vector.end(), 0);
//    std::random_shuffle(reference_vector.begin(), reference_vector.end());
//    auto input_vector = std::vector<std::pair<int, DataType>>(test_size);
//    for (auto i = 0; i < max_array_size; ++i)
//    {
//        input_vector[i].first = i / array_size;
//        input_vector[i].second[0] = reference_vector[i];
//    }
//    auto n_output_lists = test_size / array_size;
//    auto output_lists = std::vector<std::list<DataType>>(n_output_lists);
//    for (auto _ : state)
//    {
//        for (auto& input_pair : input_vector)
//        {
//            auto& current_list = output_lists[input_pair.first];
//            auto current_value = input_pair.second;
//            auto it = current_list.begin();
//            for (; it != current_list.end(); ++it)
//            {
//                if (current_value[0] < (*it)[0]) { break; }
//            }
//            benchmark::DoNotOptimize(current_list.insert(it, current_value));
//        }
//    }
//    state.SetItemsProcessed(state.iterations()*test_size);
//}

//BENCHMARK_TEMPLATE(BM_vector_insert_in_sorted_order, 1)->RangeMultiplier(2)->Range(1 << 2, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_list_insert_in_sorted_order, 1)->RangeMultiplier(2)->Range(1 << 2, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_vector_insert_in_sorted_order, 8)->RangeMultiplier(2)->Range(1 << 5, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_list_insert_in_sorted_order, 8)->RangeMultiplier(2)->Range(1 << 5, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_vector_insert_in_sorted_order, 64)->RangeMultiplier(2)->Range(1 << 8, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_list_insert_in_sorted_order, 64)->RangeMultiplier(2)->Range(1 << 8, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_vector_insert_in_sorted_order, 512)->RangeMultiplier(2)->Range(1 << 11, max_array_bytes)->Iterations(1);
//BENCHMARK_TEMPLATE(BM_list_insert_in_sorted_order, 512)->RangeMultiplier(2)->Range(1 << 11, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 4, std::vector)->RangeMultiplier(2)->Range(1 << 2, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 4, std::list)->RangeMultiplier(2)->Range(1 << 2, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 32, std::vector)->RangeMultiplier(2)->Range(1 << 5, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 32, std::list)->RangeMultiplier(2)->Range(1 << 5, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 256, std::vector)->RangeMultiplier(2)->Range(1 << 8, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 256, std::list)->RangeMultiplier(2)->Range(1 << 8, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 2048, std::vector)->RangeMultiplier(2)->Range(1 << 11, max_array_bytes)->Iterations(1);
BENCHMARK_TEMPLATE2(BM_insert_in_sorted_order, 2048, std::list)->RangeMultiplier(2)->Range(1 << 11, max_array_bytes)->Iterations(1);

BENCHMARK_MAIN();