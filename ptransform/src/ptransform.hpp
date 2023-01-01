#pragma once
#include <algorithm>
#include <vector>
#include <future>
#include <numeric>

constexpr uint64_t min_size_of_container = 100'000;
constexpr uint64_t max_count_of_threads = 9;

class tr {    
	uint64_t count_of_threads_;
public:
    tr() : count_of_threads_(1) {}
    explicit tr(const uint64_t count_of_threads)
	: count_of_threads_(count_of_threads < max_count_of_threads ? count_of_threads : max_count_of_threads){}

	template< class InputIt, class OutputIt, class UnaryOperation,
        typename = std::enable_if<std::is_same_v<typename std::iterator_traits<OutputIt>::iterator_category, std::random_access_iterator_tag>>>
	constexpr OutputIt ptransform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op) {
        if (last1 - first1 < min_size_of_container || count_of_threads_ == 1) {
            return std::transform(first1, last1, d_first, unary_op);
        }
        auto intervals = make_intervals(last1 - first1);
        std::vector<std::future<OutputIt>> all_futures(intervals.size() - 1);
        for (uint64_t i = 0; i < intervals.size() - 1; ++i) {
            all_futures[i] = std::async(std::launch::async, std::transform<InputIt, OutputIt, UnaryOperation>,
                first1 + intervals[i], first1 + intervals[i + 1], d_first + intervals[i], unary_op);
        }
        for (uint64_t i = 0; i < intervals.size() - 1; i++) {
            all_futures[i].get();
        }
        return d_first;
    }

	template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation,
        typename = std::enable_if<std::is_same_v<typename std::iterator_traits<OutputIt>::iterator_category, std::random_access_iterator_tag>>>
	constexpr OutputIt ptransform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op) {
        if (last1 - first1 < min_size_of_container || count_of_threads_ == 1) {
            return std::transform(first1, last1, first2, d_first, binary_op);
        }
        const std::vector<uint64_t> intervals = make_intervals(last1 - first1);
        std::vector<std::future<OutputIt>> all_futures(intervals.size() - 1);
        for (uint64_t i = 0; i < intervals.size() - 1; ++i) {
            all_futures[i] = std::async(std::launch::async, std::transform<InputIt1, InputIt2, OutputIt, BinaryOperation>,
                first1 + intervals[i], first1 + intervals[i + 1], first2 + intervals[i], d_first + intervals[i], binary_op);
        }
        for (uint64_t i = 0; i < intervals.size() - 1; i++) {
            all_futures[i].get();
        }
        return d_first;
    }

    [[nodiscard]] uint64_t get_max_count_of_threads() const noexcept;
private:
    [[nodiscard]] std::vector<uint64_t> make_intervals(const uint64_t input_num) const;
};
