#pragma once
#include <string>

template<typename T>
struct SumType
{
    using sumType = T;
};

template<>
struct SumType<std::string>
{
    using sumType = std::string;
};

template<>
struct SumType<char>
{
    using sumType = std::string;
};

template<>
struct SumType<int>
{
public:
    using sumType = long long;
};

template<>
struct SumType<double>
{
    using sumType = long double;
};