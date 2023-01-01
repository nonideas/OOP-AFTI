#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

class WordPalindrome final
{
	std::string word;
	bool is_palindrome;
public:
	WordPalindrome(std::string word, bool is_palindrome)
		: word{word}, is_palindrome{is_palindrome} {}
	std::string get_word() const {
		return word;
	}
	bool get_is_palindrome() const {
		return is_palindrome;
	}
};

class Palindrome final
{
private:
	std::string sentense;
	std::vector<WordPalindrome> is_words_palindrome;
	bool is_sentence_palindrome;
	bool is_word_set_palindrome;
public:
	Palindrome(std::istream& file);

	std::string GetSentense() const {
		return sentense;
	}
	std::vector<WordPalindrome> GetIsWordPalindrome() const {
		return is_words_palindrome;
	}
	bool GetIsSentensePalindrome() const {
		return is_sentence_palindrome;
	}
	bool GetIsWordSetPalindrome() const {
		return is_word_set_palindrome;
	}

	std::ostringstream output_stream() const;
};
