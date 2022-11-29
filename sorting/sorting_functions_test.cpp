#include "sorting_functions.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <numeric>
#include <vector>

TEST(QuickSort, MaintainSortedArray)
{
    auto reference_vector = std::vector<int>(1 << 10);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    auto copy_vector = reference_vector;
    quick_sort(copy_vector.begin(), copy_vector.end());
    for (auto i = 0; i < copy_vector.size(); ++i)
    {
        EXPECT_EQ(copy_vector[i], reference_vector[i]);
    }
}

TEST(QuickSort, SortShuffledArray)
{
    auto reference_vector = std::vector<int>(1 << 10);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    auto copy_vector = reference_vector;
    std::random_shuffle(copy_vector.begin(), copy_vector.end());
    quick_sort(copy_vector.begin(), copy_vector.end());
    for (auto i = 0; i < copy_vector.size(); ++i)
    {
        EXPECT_EQ(copy_vector[i], reference_vector[i]);
    }
}

TEST(InsertionSort, MaintainSortedArray)
{
    auto reference_vector = std::vector<int>(1 << 10);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    auto copy_vector = reference_vector;
    insertion_sort(copy_vector.begin(), copy_vector.end());
    for (auto i = 0; i < copy_vector.size(); ++i)
    {
        EXPECT_EQ(copy_vector[i], reference_vector[i]);
    }
}

TEST(InsertionSort, SortShuffledArray)
{
    auto reference_vector = std::vector<int>(1 << 10);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    auto copy_vector = reference_vector;
    std::random_shuffle(copy_vector.begin(), copy_vector.end());
    insertion_sort(copy_vector.begin(), copy_vector.end());
    for (auto i = 0; i < copy_vector.size(); ++i)
    {
        EXPECT_EQ(copy_vector[i], reference_vector[i]);
    }
}

TEST(BubbleSort, MaintainSortedArray)
{
    auto reference_vector = std::vector<int>(1 << 10);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    auto copy_vector = reference_vector;
    bubble_sort(copy_vector.begin(), copy_vector.end());
    for (auto i = 0; i < copy_vector.size(); ++i)
    {
        EXPECT_EQ(copy_vector[i], reference_vector[i]);
    }
}

TEST(BubbleSort, SortShuffledArray)
{
    auto reference_vector = std::vector<int>(1 << 10);
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    auto copy_vector = reference_vector;
    std::random_shuffle(copy_vector.begin(), copy_vector.end());
    bubble_sort(copy_vector.begin(), copy_vector.end());
    for (auto i = 0; i < copy_vector.size(); ++i)
    {
        EXPECT_EQ(copy_vector[i], reference_vector[i]);
    }
}