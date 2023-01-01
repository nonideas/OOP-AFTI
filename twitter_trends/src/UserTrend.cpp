#include "UserTrend.h"
#include <unordered_set>

double UserTrend::calculate_user_trend(const std::unordered_set <std::string>& top_n, const User& user)
{
	int all_hashtags_count = 0;
	int trend_hashtags_count = 0;
	auto tweets = user.get_tweets();
	for (auto tweet = tweets.begin(); tweet != tweets.end(); ++tweet) {
		auto hashtags = tweet->get_hashtags();
		for (auto hashtag = hashtags.begin(); hashtag != hashtags.end(); ++hashtag) {
		
			if (top_n.find(*hashtag) != top_n.end()) {
				++trend_hashtags_count;
			}
			++all_hashtags_count;
		}
	}
	double trend = 0;
	if (all_hashtags_count != 0) {
		trend = (double)trend_hashtags_count / all_hashtags_count;
	}
	return trend;
}
