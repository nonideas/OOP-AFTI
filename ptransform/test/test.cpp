#include "gtest/gtest.h"
#include "../src/ptransform.hpp"

TEST(binagy, treads1) {
	tr t(1);

    std::vector<uint32_t> ordinals;
    std::vector<uint32_t> ordinals_true;
    for (int i = 0; i < 200000; ++i) {
        ordinals_true.push_back(i);
        ordinals.push_back(i);
    }
    std::transform(ordinals_true.cbegin(), ordinals_true.cend(), ordinals_true.cbegin(),
        ordinals_true.begin(), std::plus<>{});
    t.ptransform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
        ordinals.begin(), std::plus<>{});
    for (uint32_t i = 0; i < ordinals.size(); ++i) {
        EXPECT_EQ(ordinals[i], ordinals_true[i]);
    }
}

TEST(binagy, treads2) {
    tr t(2);

    std::vector<uint32_t> ordinals;
    std::vector<uint32_t> ordinals_true;
    for (int i = 0; i < 200000; ++i) {
        ordinals_true.push_back(i);
        ordinals.push_back(i);
    }
    std::transform(ordinals_true.cbegin(), ordinals_true.cend(), ordinals_true.cbegin(),
        ordinals_true.begin(), std::plus<>{});
    t.ptransform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
        ordinals.begin(), std::plus<>{});
    for (uint32_t i = 0; i < ordinals.size(); ++i) {
        EXPECT_EQ(ordinals[i], ordinals_true[i]);
    }
}

TEST(binagy, treads3) {
    tr t(3);

    std::vector<uint32_t> ordinals;
    std::vector<uint32_t> ordinals_true;
    for (int i = 0; i < 200000; ++i) {
        ordinals_true.push_back(i);
        ordinals.push_back(i);
    }
    std::transform(ordinals_true.cbegin(), ordinals_true.cend(), ordinals_true.cbegin(),
        ordinals_true.begin(), std::plus<>{});
    t.ptransform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
        ordinals.begin(), std::plus<>{});
    for (uint32_t i = 0; i < ordinals.size(); ++i) {
        EXPECT_EQ(ordinals[i], ordinals_true[i]);
    }
}

TEST(binagy, treads8) {
    tr t(8);

    std::vector<uint32_t> ordinals;
    std::vector<uint32_t> ordinals_true;
    for (int i = 0; i < 200000; ++i) {
        ordinals_true.push_back(i);
        ordinals.push_back(i);
    }
    std::transform(ordinals_true.cbegin(), ordinals_true.cend(), ordinals_true.cbegin(),
        ordinals_true.begin(), std::plus<>{});
    t.ptransform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
        ordinals.begin(), std::plus<>{});
    for (uint32_t i = 0; i < ordinals.size(); ++i) {
        EXPECT_EQ(ordinals[i], ordinals_true[i]);
    }
}

TEST(unary, tread1) {
    tr t(1);
    std::string s;
    std::string s_true;
    for (int i = 0; i < 200000; ++i) {
        s.push_back('a');
        s_true.push_back('a');
    }
    std::transform(s_true.cbegin(), s_true.cend(),s_true.begin(), 
        [](unsigned char c) { return std::toupper(c); });
    t.ptransform(s.cbegin(), s.cend(), s.begin(), 
        [](unsigned char c) { return std::toupper(c); });
    EXPECT_EQ(s, s_true);
}

TEST(unary, tread2) {
    tr t(2);
    std::string s;
    std::string s_true;
    for (int i = 0; i < 200000; ++i) {
        s.push_back('a');
        s_true.push_back('a');
    }
    std::transform(s_true.cbegin(), s_true.cend(), s_true.begin(),
        [](unsigned char c) { return std::toupper(c); });
    t.ptransform(s.cbegin(), s.cend(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    EXPECT_EQ(s, s_true);
}

TEST(unary, tread3) {
    tr t(3);
    std::string s;
    std::string s_true;
    for (int i = 0; i < 200000; ++i) {
        s.push_back('a');
        s_true.push_back('a');
    }
    std::transform(s_true.cbegin(), s_true.cend(), s_true.begin(),
        [](unsigned char c) { return std::toupper(c); });
    t.ptransform(s.cbegin(), s.cend(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    EXPECT_EQ(s, s_true);
}

TEST(unary, tread8) {
    tr t(8);
    std::string s;
    std::string s_true;
    for (int i = 0; i < 200000; ++i) {
        s.push_back('a');
        s_true.push_back('a');
    }
    std::transform(s_true.cbegin(), s_true.cend(), s_true.begin(),
        [](unsigned char c) { return std::toupper(c); });
    t.ptransform(s.cbegin(), s.cend(), s.begin(),
        [](unsigned char c) { return std::toupper(c); });
    EXPECT_EQ(s, s_true);
}