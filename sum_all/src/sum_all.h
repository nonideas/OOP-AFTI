#pragma once
#include "types.h"

namespace sum_all
{
    template<class T>
    auto sum_all(const T& v) {
        return v;
    }

    template<template<class, class> class Container, class Type, class Allocator = std::allocator<Type>,
        typename = std::enable_if_t<std::is_default_constructible_v<Type>>>
	auto sum_all(const Container<Type, Allocator>& v) {
        typename SumType<Type>::sumType res{};
        for (const auto& i : v) {
            res = res + i;
        }
        return res;
    }

    template<template<class, class, class, class> class Map, class Key, class Type,
        class Traits = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, Type>>,
        typename = std::enable_if_t<std::is_default_constructible_v<Type>>>
	auto sum_all(const Map<Key, Type, Traits, Allocator>& v) {
        typename SumType<Type>::sumType res{};
        for (const auto& [key, type] : v) {
            res = res + type;
        }
        return res;
    }
}
