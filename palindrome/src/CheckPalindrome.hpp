#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace CheckPalindrome
{
	bool check_word_for_palindrome(std::string word);
	bool check_sentence_for_palindrome(const std::string& sentence);
	bool check_word_set_for_palindrome(const std::string& sentence);
}
