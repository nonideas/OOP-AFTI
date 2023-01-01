#pragma once
#include "User.h"
#include "UserTrend.h"
#include "Parser.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <optional>

class UsersManager final {
	// std::size_t is the user_id
	std::unordered_map<std::size_t, User> users;
public:
	UsersManager(const Parser::ParseTweets& tweets);
	void add_tweet(const Parser::ParseTweet& tweet);
	void delete_tweet(const std::size_t& user_id, const std::time_t& ts);

	std::unordered_set<std::string> find_top_n(int n, const std::time_t& start, const std::time_t& end);
	std::optional<double> calculate_user_trend(const std::size_t& user_id, const std::unordered_set<std::string>& top_n);

	const std::unordered_map<std::size_t, User>& get_users() const {
		return users;
	}
	~UsersManager() = default;
};
