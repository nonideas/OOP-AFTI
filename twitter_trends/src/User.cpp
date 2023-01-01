#include "User.h"
#include "Parser.h"
#include <iostream>

using namespace std;

void User::add_user_profile(const std::size_t& user_id, const std::time_t& ts, const std::vector<std::string>& hashtags)
{
	this->user_id = user_id;
	this->tweets.push_back(Tweet(ts, hashtags));
}

void User::delete_tweet(const std::time_t& ts)
{
	auto it = this->tweets.begin();
	while (it != this->tweets.end())
		if ((*it).get_ts() == ts) {
			it = this->tweets.erase(it);
		}
		else {
			++it;
		}
}
