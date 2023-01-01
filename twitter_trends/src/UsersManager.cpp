#include "UsersManager.h"
#include "Parser.h"
#include <unordered_set>

using namespace std;

UsersManager::UsersManager(const Parser::ParseTweets& tweets)
{
	if (tweets.get_tweets().size() > 0) {
		std::vector<Parser::ParseTweet> tw = tweets.get_tweets();
		for (auto tweet_pointer = tw.begin(); tweet_pointer != tw.end(); ++tweet_pointer) {
			this->users[tweet_pointer->get_user_id()].add_user_profile(tweet_pointer->get_user_id(), tweet_pointer->get_ts(), tweet_pointer->get_hashtags());
		}
	}
}

void UsersManager::add_tweet(const Parser::ParseTweet& tweet)
{
	this->users[tweet.get_user_id()].add_user_profile(tweet.get_user_id(), tweet.get_ts(), tweet.get_hashtags());
}

void UsersManager::delete_tweet(const std::size_t& user_id, const std::time_t& ts)
{
	if (this->users.find(user_id) != this->users.end()) {
		this->users[user_id].delete_tweet(ts);
	}
}

unordered_set <string> UsersManager::find_top_n(int n, const std::time_t& start, const std::time_t& end)
{
	unordered_set <string> top_n;
	unordered_map <std::string, size_t> hashtags_count;

	for (auto user_pointer = users.begin(); user_pointer != users.end(); ++user_pointer) {
		auto tweets = user_pointer->second.get_tweets();
		for (auto tweet_pointer = tweets.begin(); tweet_pointer != tweets.end(); ++tweet_pointer) {
			if (tweet_pointer->get_ts() >= start && tweet_pointer->get_ts() <= end) {
				auto hashtags = tweet_pointer->get_hashtags();
				for (auto hashtag_pointer = hashtags.begin(); hashtag_pointer != hashtags.end(); ++hashtag_pointer) {
					hashtags_count[*hashtag_pointer]++;
				}
			}
		}
	}
	while (n > 0 && hashtags_count.size() > 0) {
		auto top_hashtag = hashtags_count.begin();
		for (auto hc = hashtags_count.begin(); hc != hashtags_count.end(); ++hc) {
			if (hc->second > top_hashtag->second) {
				top_hashtag = hc;
			}
		}
		top_n.insert(top_hashtag->first);
		hashtags_count.erase(top_hashtag);
		n--;
	}
	return top_n;
}

std::optional<double> UsersManager::calculate_user_trend(const std::size_t& user_id, const unordered_set <string>& top_n)
{
	if (users.find(user_id) != users.end()) {
		return  UserTrend::calculate_user_trend(top_n, this->users[user_id]);
	}
	else {
		return {};
	}
}