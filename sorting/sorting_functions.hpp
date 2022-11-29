#pragma once

#include <iterator>

template <std::random_access_iterator Iter>
auto quick_sort(Iter first, Iter last) -> void
{
    auto partition = [](Iter f, Iter l)
    {
        auto pivot = *(l - 1);
        auto i = -1;
        for (auto current = f; current != l; ++current)
        {
            if (*current < pivot)
            {
                ++i;
                std::swap(*(f + i), *current);
            }
        }
        std::swap(*(f + i + 1), *(l - 1));
        return f + i + 1;
    };

    if (first != last)
    {
        auto part_it = partition(first, last);
        quick_sort(first, part_it);
        quick_sort(part_it + 1, last);
    }
}

//template <std::random_access_iterator Iter>
//auto merge_sort(Iter first, Iter last) -> void
//{
//}

template <std::random_access_iterator Iter>
auto insertion_sort(Iter first, Iter last) -> void
{
    for (auto insert_it = first + 1; insert_it != last; ++insert_it)
    {
        auto search_it = insert_it - 1;
        auto insert_value = *insert_it;
        for (; search_it >= first and insert_value < *(search_it); --search_it)
        {
            *(search_it + 1) = *search_it;
        }
        *(search_it + 1) = insert_value;
    }
}

template <std::random_access_iterator Iter>
auto bubble_sort(Iter first, Iter last) -> void
{
    for (auto sort_end = last; sort_end != first + 1; --sort_end)
    {
        for (auto bubble_it = first; bubble_it != sort_end - 1; ++bubble_it)
        {
            if (*bubble_it > *(bubble_it + 1)) { std::swap(*bubble_it, *(bubble_it + 1)); }
        }
    }
}