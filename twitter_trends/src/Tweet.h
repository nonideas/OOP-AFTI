#pragma once
#include <ctime>
#include <string>
#include <vector>

class Tweet final {
	std::time_t ts;
	std::vector<std::string> hashtags;
public:
	Tweet(const std::time_t& ts, const std::vector<std::string>& hashtags);
	~Tweet() = default;

	const std::time_t& get_ts() const {
		return ts;
	}
	const std::vector<std::string>& get_hashtags() const {
		return hashtags;
	}
};