#include "gtest/gtest.h"
#include "../src/sum_all.h"
#include "../src/sum_all_concept.h"
#include <vector>
#include <string>
#include <list>
#include <map>

using namespace std;

TEST(SingleArg, OneArg) {
    EXPECT_EQ(sum_all::sum_all(3), 3);
    EXPECT_EQ(sum_all::sum_all('a'), 'a');
    EXPECT_EQ(sum_all::sum_all(3.3), 3.3);
    EXPECT_EQ(sum_all::sum_all(true), true);

    EXPECT_EQ(sum_all_concept::sum_all(3), 3);
    EXPECT_EQ(sum_all_concept::sum_all('a'), 'a');
    EXPECT_EQ(sum_all_concept::sum_all(3.3), 3.3);
    EXPECT_EQ(sum_all_concept::sum_all(true), true);
}

TEST(Range, Vectors) {
    vector<int> v1 = { 1, 2, 3 };
    auto i1 = std::counted_iterator{ v1.begin(), std::ssize(v1) };
    auto r1 = std::ranges::subrange{ i1, std::default_sentinel };

    vector<double> v2 = { 1, 2, 3 };
    auto i2 = std::counted_iterator{ v2.begin(), std::ssize(v2) };
    auto r2 = std::ranges::subrange{ i2, std::default_sentinel };

    vector<string> v3 = { "a", "bc", "def" };
    auto i3 = std::counted_iterator{ v3.begin(), std::ssize(v3) };
    auto r3 = std::ranges::subrange{ i3, std::default_sentinel };

    vector<char> v4 = { 'a', 'b', 'c' };
    auto i4 = std::counted_iterator{ v4.begin(), std::ssize(v4) };
    auto r4 = std::ranges::subrange{ i4, std::default_sentinel };

    EXPECT_EQ(sum_all_concept::sum_all(r1), 6);
    EXPECT_EQ(sum_all_concept::sum_all(r2), 6.0);
    EXPECT_EQ(sum_all_concept::sum_all(r3), "abcdef");
    EXPECT_EQ(sum_all_concept::sum_all(r4), "abc");
}

TEST(Range, List) {
    list<int> v1 = {  };
    auto i1 = std::counted_iterator{ v1.begin(), std::ssize(v1) };
    auto r1 = std::ranges::subrange{ i1, std::default_sentinel };

    list<double> v2 = { 1, 2, 3 };
    auto i2 = std::counted_iterator{ v2.begin(), std::ssize(v2) };
    auto r2 = std::ranges::subrange{ i2, std::default_sentinel };

    list<string> v3 = { "a", "bc", "def" };
    auto i3 = std::counted_iterator{ v3.begin(), std::ssize(v3) };
    auto r3 = std::ranges::subrange{ i3, std::default_sentinel };

    list<char> v4 = { 'a', 'b', 'c' };
    auto i4 = std::counted_iterator{ v4.begin(), std::ssize(v4) };
    auto r4 = std::ranges::subrange{ i4, std::default_sentinel };

    EXPECT_EQ(sum_all_concept::sum_all(r1), 0);
    EXPECT_EQ(sum_all_concept::sum_all(r2), 6.0);
    EXPECT_EQ(sum_all_concept::sum_all(r3), "abcdef");
    EXPECT_EQ(sum_all_concept::sum_all(r4), "abc");
}

TEST(Containers, Vectors) {
    vector<int> v1 = { 1, 2, 3 };
    vector<double> v2 = { 1, 2, 3 };
    vector<string> v3 = { "a", "bc", "def" };
    vector<char> v4 = { 'a', 'b', 'c' };

    EXPECT_EQ(sum_all::sum_all(v1), 6);
    EXPECT_EQ(sum_all::sum_all(v2), 6.0);
    EXPECT_EQ(sum_all::sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all::sum_all(v4), "abc");

    EXPECT_EQ(sum_all_concept::sum_all(v1), 6);
    EXPECT_EQ(sum_all_concept::sum_all(v2), 6.0);
    EXPECT_EQ(sum_all_concept::sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all_concept::sum_all(v4), "abc");
}


TEST(Containers, List) {
    list<int> v1 = {  };
    list<double> v2 = { 1, 2, 3 };
    list<string> v3 = { "a", "bc", "def" };
    list<char> v4 = { 'a', 'b', 'c' };

    EXPECT_EQ(sum_all::sum_all(v1), 0);
    EXPECT_EQ(sum_all::sum_all(v2), 6.0);
    EXPECT_EQ(sum_all::sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all::sum_all(v4), "abc");

    EXPECT_EQ(sum_all_concept::sum_all(v1), 0);
    EXPECT_EQ(sum_all_concept::sum_all(v2), 6.0);
    EXPECT_EQ(sum_all_concept::sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all_concept::sum_all(v4), "abc");
}

TEST(Containers, Map) {
    map<int, int> v1 = { {1, 1}, {2, 2}, {3, 3} };
    map<int, double> v2 = { {1, 1}, {2, 2}, {3, 3} };
    map<int, std::string> v3 = { {1, "a"}, {2, "bc"}, {3, "def"} };
    map<int, char> v4 = { {1, 'a'}, {2, 'b'}, {3, 'c'} };

    EXPECT_EQ(sum_all::sum_all(v1), 6);
    EXPECT_EQ(sum_all::sum_all(v2), 6.0);
    EXPECT_EQ(sum_all::sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all::sum_all(v4), "abc");

    EXPECT_EQ(sum_all_concept::sum_all(v1), 6);
    EXPECT_EQ(sum_all_concept::sum_all(v2), 6.0);
    EXPECT_EQ(sum_all_concept::sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all_concept::sum_all(v4), "abc");
}
