#pragma once
#include <concepts>
#include <ranges>
#include <numeric>
#include "types.h"

namespace sum_all_concept
{
    template <class Type>
    concept IsDefaultContsructible = requires() {
        std::is_default_constructible_v<Type>;
    };

    template<class T>
    auto sum_all(const T& v) {
        return v;
    }

    template <std::ranges::range Range>
    auto sum_all(const Range& range) {
        typename SumType<std::ranges::range_value_t<Range>>::sumType res{};
        for (const auto& i : range) {
            res = res + i;
        }
        return res;
    }
    
    template<template<class, class, class, class> class Map, class Key, class Type,
        class Traits = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, Type>>>
    requires IsDefaultContsructible < Type >
    auto sum_all(const Map<Key, Type, Traits, Allocator>& v) {
        typename SumType<Type>::sumType res{};
        for (const auto& [key, type] : v) {
            res = res + type;
        }
        return res;
    }
}