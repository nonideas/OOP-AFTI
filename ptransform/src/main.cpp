#include "ptransform.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

int xform(int i) {
    return i * i;
}

void binary_operation_test(std::ostream& stream)
{
    stream << "binary operation:" << std::endl;
    const auto dimensions = { 10'000, 100'000, 1'000'000,  5'000'000, 10'000'000 };


    stream << std::setw(8) << "th/dim";
    for (size_t th = 1; th <= 9; ++th) {
        stream << std::setw(12) << th;
    }
    stream << std::endl;
    for (const auto dim : dimensions) {
        std::vector<uint32_t> val(dim);
        std::vector<uint32_t> res(val.size());
        stream << std::setw(8) << dim;
    	stream.flush();
        for (size_t th = 1; th <= 9; ++th) {
            tr t(th);
            auto start = std::chrono::high_resolution_clock::now();
            t.ptransform(val.cbegin(), val.cend(), val.cbegin(),
                res.begin(), std::plus<>{});
            double time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
            stream << std::setw(12) << std::setprecision(7) << std::fixed << time;
        	stream.flush();
        }
        stream << std::endl;
    }
}

void unary_operation_test(std::ostream& stream)
{
    stream << "unary operation:" << std::endl;
    const auto dimensions = { 10'000, 100'000, 1'000'000,  5'000'000, 10'000'000 };


    stream << std::setw(8) << "th/dim";
    for (size_t th = 1; th <= 9; ++th) {
        stream << std::setw(12) << th;
    }
    stream << std::endl;
    for (const auto dim : dimensions) {
        std::vector<uint32_t> val(dim);
        std::vector<uint32_t> res(val.size());
        stream << std::setw(8) << dim;
        stream.flush();
        for (size_t th = 1; th <= 9; ++th) {
            tr t(th);
            auto start = std::chrono::high_resolution_clock::now();
            t.ptransform(val.cbegin(), val.cend(), res.begin(), xform);
            double time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
            stream << std::setw(12) << std::setprecision(7) << std::fixed << time;
            stream.flush();
        }
        stream << std::endl;
    }
}

int main(int argc, char** argv) {
    std::ofstream st("test/results.txt");
    binary_operation_test(st);
    unary_operation_test(st);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}