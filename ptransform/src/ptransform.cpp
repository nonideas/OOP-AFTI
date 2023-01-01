#include "ptransform.hpp"

uint64_t tr::get_max_count_of_threads() const noexcept
{
    return count_of_threads_;
}

std::vector<uint64_t> tr::make_intervals(const uint64_t input_num) const
{
    std::vector<uint64_t> intervals;
    const uint64_t distance = input_num / count_of_threads_;
    uint64_t current_pos = 0;
    intervals.emplace_back(current_pos);
    for (uint64_t i = 1; i < count_of_threads_; i++) {
        intervals.emplace_back(current_pos + distance);
        current_pos += distance;
    }
    intervals[count_of_threads_ - 1] = input_num;
    return intervals;
}
