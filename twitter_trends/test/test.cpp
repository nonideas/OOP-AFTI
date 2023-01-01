#include "test.h"

class MemoryLeakDetector {
public:
	MemoryLeakDetector() {
		_CrtMemCheckpoint(&memState_);
	}

	~MemoryLeakDetector() {
		_CrtMemState stateNow, stateDiff;
		_CrtMemCheckpoint(&stateNow);
		int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
		if (diffResult)
			reportFailure(stateDiff.lSizes[1]);
	}
private:
	void reportFailure(unsigned int unfreedBytes) {
		FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
	}
	_CrtMemState memState_;
};

TEST(TestCreateTweets, NoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	ASSERT_EQ(users.get_users().size(), 0);
}

TEST(TestCreateTweets, OneTweetNoHashtags) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	ASSERT_EQ(users.get_users().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_user_id(), 228);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_ts(), 2000);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags().size(), 0);
}

TEST(TestCreateTweets, OneTweet) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <www>, <eee>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags().size(), 3);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[0], "www");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[1], "www");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[2], "eee");
}

TEST(TestCreateTweets, TwoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <eee>\n337 2012 <www>, <www>, <qqq>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	ASSERT_EQ(users.get_users().size(), 2);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags().size(), 2);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_hashtags().size(), 3);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[0], "www");
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_hashtags()[1], "www");
	ASSERT_EQ(users.get_users().at(337).get_user_id(), 337);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_ts(), 2012);
}

TEST(TestCreateTweets, TwoTweetsOneUser) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <qqq>, <www>, <eee>\n228 2012 <www>, <www>, <qqq>, <sss>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	ASSERT_EQ(users.get_users().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[2], "eee");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[1].get_hashtags()[2], "qqq");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[1].get_hashtags()[3], "sss");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[1].get_hashtags().size(), 4);
}

TEST(TestDeleteTweets, NoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	users.delete_tweet(228, 2000);
	ASSERT_EQ(users.get_users().size(), 0);
}

TEST(TestDeleteTweets, OneTweetNoHashtags) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	users.delete_tweet(228, 2000);
	ASSERT_EQ(users.get_users().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_user_id(), 228);
	ASSERT_EQ(users.get_users().at(228).get_tweets().size(), 0);
}

TEST(TestDeleteTweets, OneTweet) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <www>, <eee>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	users.delete_tweet(228, 2000);
	ASSERT_EQ(users.get_users().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_user_id(), 228);
	ASSERT_EQ(users.get_users().at(228).get_tweets().size(), 0);
}

TEST(TestDeleteTweets, TwoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <eee>\n337 2012 <www>, <www>, <qqq>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	users.delete_tweet(228, 2000);
	ASSERT_EQ(users.get_users().size(), 2);
	ASSERT_EQ(users.get_users().at(228).get_tweets().size(), 0);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_hashtags().size(), 3);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_hashtags()[1], "www");
	ASSERT_EQ(users.get_users().at(337).get_user_id(), 337);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_ts(), 2012);
}

TEST(TestDeleteTweets, TwoTweetsOneUser) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <qqq>, <www>, <eee>\n228 2012 <www>, <www>, <qqq>, <sss>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	users.delete_tweet(228, 2000);
	ASSERT_EQ(users.get_users().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_tweets().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[0], "www");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[2], "qqq");
}

TEST(TestAddTweets, TwoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <www>, <eee>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	Parser::ParseTweet tweet("228 2012 <www>, <www>, <qqq>, <sss>");
	users.add_tweet(tweet);
	ASSERT_EQ(users.get_users().size(), 1);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[2], "eee");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[1].get_hashtags()[2], "qqq");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[1].get_hashtags()[3], "sss");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[1].get_hashtags().size(), 4);
}

TEST(TestAddTweets, TwoTweetsOneUser) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <eee>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	Parser::ParseTweet tweet("337 2012 <www>, <www>, <qqq>, <sss>");
	users.add_tweet(tweet);
	ASSERT_EQ(users.get_users().size(), 2);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags().size(), 2);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_hashtags().size(), 4);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[0], "www");
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_hashtags()[1], "www");
	ASSERT_EQ(users.get_users().at(337).get_user_id(), 337);
	ASSERT_EQ(users.get_users().at(337).get_tweets()[0].get_ts(), 2012);
}

TEST(TestAddTweets, OneTweet) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <www>, <www>, <eee>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	Parser::ParseTweet tweet("");
	users.add_tweet(tweet);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags().size(), 3);
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[0], "www");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[1], "www");
	ASSERT_EQ(users.get_users().at(228).get_tweets()[0].get_hashtags()[2], "eee");
}

TEST(TestTopN, NoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	std::unordered_set <std::string> top_n = users.find_top_n(5, 2000, 2033);
	ASSERT_EQ(top_n.size(), 0);
}

TEST(TestTopN, TwoTweetsOneUser) {
	std::stringstream stream("228 2000 <qqq>, <www>, <eee>\n228 2012 <www>, <www>, <qqq>, <sss>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	std::unordered_set <std::string> top_n = users.find_top_n(2, 1999, 2333);
	ASSERT_EQ(top_n.size(), 2);
	ASSERT_NE(top_n.find("www"), top_n.end());
	ASSERT_NE(top_n.find("qqq"), top_n.end());
}

TEST(TestTrendiness, NoTweets) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	auto trend = users.calculate_user_trend(228, users.find_top_n(5, 2000, 2033));
	if (trend.has_value())
	{
		ASSERT_EQ(trend.value(), 0.625);
	}
	ASSERT_EQ(users.get_users().size(), 0);
}

TEST(TestTrendiness, TwoTweetsOneUser) {
	MemoryLeakDetector leakDetector;
	std::stringstream stream("228 2000 <qqq>, <www>, <eee>\n228 2012 <www>, <www>, <qqq>, <sss>, <aaa>");
	Parser::ParseTweets tweets(stream);
	UsersManager users(tweets);
	auto trend = users.calculate_user_trend(228, users.find_top_n(2, 1999, 2333));
	if (trend)
	{
		ASSERT_EQ(*trend, 0.625);
	}
}
