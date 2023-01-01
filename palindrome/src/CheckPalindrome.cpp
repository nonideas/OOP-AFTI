#include "CheckPalindrome.hpp"
#include "ChangeSentence.hpp"

using namespace std;

bool CheckPalindrome::check_word_for_palindrome(string word)
{
	word = ChangeSentence::to_low(word);
	return word == ChangeSentence::reverse_word(word);
}

bool CheckPalindrome::check_sentence_for_palindrome(const string& sentence)
{
	vector<std::string> words = ChangeSentence::separate_sentence(sentence);
	return check_word_for_palindrome(ChangeSentence::concatenation_words(words));
}

bool CheckPalindrome::check_word_set_for_palindrome(const string& sentence)
{
	vector<std::string> words = ChangeSentence::separate_sentence(sentence);

	for (int start = 0, end = words.size() - 1; start < end; start++, end--) {
		if (!(ChangeSentence::to_low(words[start]) == ChangeSentence::to_low(words[end]))) {
			return false;
		}
	}
	return true;
}


