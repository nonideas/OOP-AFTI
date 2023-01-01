#include "ChangeSentence.hpp"

using namespace std;

vector<string> ChangeSentence::separate_sentence(const string& sentence)
{
	vector<string> words;
	for (size_t pos = 0;;) {
		pos = sentence.find_first_not_of(" \t,.", pos);
		if (pos == string::npos) {
			break;
		}
		size_t pos_end = sentence.find_first_of(" \t,.", pos);
		size_t len = (pos_end == string::npos) ? string::npos : pos_end - pos;

		string word(sentence.substr(pos, len));
		words.push_back(word);

		pos = pos_end;
	}
	return words;
}

string ChangeSentence::to_low(string word)
{
	std::for_each(word.begin(), word.end(), [](char& c) {
		c = ::tolower(c);
		});
	return word;
}

string ChangeSentence::reverse_word(string word)
{
	std::reverse(word.begin(), word.end());
	return word;
}

string ChangeSentence::concatenation_words(const vector<string>& words)
{
	string word = "";
	for (int i = 0; i < words.size(); i++)
	{
		word += words[i];
	}
	return word;
}
