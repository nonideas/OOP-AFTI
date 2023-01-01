#pragma once
#include <string>
#include <ctime>
#include <vector>

namespace Parser
{
	class ParseTweet final {
		std::size_t user_id;
		std::time_t ts;
		std::vector<std::string> hashtags;
	public:
		ParseTweet(const std::string& line);

		const std::size_t& get_user_id() const {
			return user_id;
		}
		const std::time_t& get_ts() const {
			return ts;
		}
		const std::vector<std::string>& get_hashtags() const {
			return hashtags;
		}
	private:
		static std::string separate_words(const std::string& line, std::size_t& pos);
	};

	class ParseTweets final {
		std::vector<ParseTweet> tweets;
	public:
		ParseTweets(std::istream& in);

		const std::vector<ParseTweet>& get_tweets() const {
			return tweets;
		}
	};
}