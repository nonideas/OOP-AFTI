#include "Parser.h"
#include <iostream>

using namespace std;

Parser::ParseTweets::ParseTweets(std::istream& in)
{
	string line;
	while (getline(in, line)) {
		if (!line.empty()) {
			this->tweets.push_back(Parser::ParseTweet(line));
		}
	}
}

Parser::ParseTweet::ParseTweet(const std::string& line)
{
	if (!line.empty()) {
		size_t pos = 0;
		this->user_id = std::stoull(separate_words(line, pos));
		this->ts = std::stoll(separate_words(line, pos));
		while (pos != string::npos) {
			string hashtag = separate_words(line, pos);
			if (hashtag.empty()) {
				break;
			}
			this->hashtags.push_back(hashtag);
		}
	}
}

std::string Parser::ParseTweet::separate_words(const std::string& line, std::size_t& pos)
{
	string separate_characters = " \t<>,";
	pos = line.find_first_not_of(separate_characters, pos);
	if (pos != string::npos) {
		size_t pos_end = line.find_first_of(separate_characters, pos);
		size_t len = (pos_end == string::npos) ? string::npos : pos_end - pos;

		string word(line.substr(pos, len));

		pos = pos_end;
		return word;
	}
	return "";
}
