#pragma once
#include "Tweet.h"
#include <string>
#include <unordered_map>
#include <vector>

class User final {
	std::size_t user_id;
	std::vector<Tweet> tweets;
public:
	void add_user_profile(const std::size_t& user_id, const std::time_t& ts, const std::vector<std::string>& hashtags);
	void delete_tweet(const std::time_t& ts);

	const std::size_t& get_user_id() const {
		return user_id;
	}
	const std::vector<Tweet>& get_tweets() const {
		return tweets;
	}
	~User() = default;
};
