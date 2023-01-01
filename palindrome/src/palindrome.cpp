#include "palindrome.h"
#include "CheckPalindrome.hpp"
#include "ChangeSentence.hpp"
#include <iostream>

using namespace std;

Palindrome::Palindrome(istream& file)
{
	string sentence;
	std::getline(file, sentence);
	this->sentense = sentence;
	vector<string> words = ChangeSentence::separate_sentence(sentence);
	for (int i = 0; i < words.size(); i++) {
		this->is_words_palindrome.push_back( { words[i], CheckPalindrome::check_word_for_palindrome(words[i]) } );
	}

	this->is_sentence_palindrome = CheckPalindrome::check_sentence_for_palindrome(sentence);

	this->is_word_set_palindrome = CheckPalindrome::check_word_set_for_palindrome(sentence);
}

std::ostringstream Palindrome::output_stream() const
{
	std::ostringstream out;
	
	
	out << this->GetSentense() << endl;

	out << endl << "Words:" << endl;
	for (int i = 0; i < this->GetIsWordPalindrome().size(); i++) {
		out << ChangeSentence::reverse_word(ChangeSentence::to_low(this->GetIsWordPalindrome()[i].get_word())) << (this->GetIsWordPalindrome()[i].get_is_palindrome() ? " - y" : " - n") << endl;
	}

	out << endl << "Sentence as a word:" << endl;
	out << ChangeSentence::reverse_word(ChangeSentence::to_low(ChangeSentence::concatenation_words(ChangeSentence::separate_sentence(this->GetSentense())))) << (this->GetIsSentensePalindrome() ? " - y" : " - n") << endl;

	out << endl << "Sentence as a word set" << endl;
	for (int i = this->GetIsWordPalindrome().size() - 1; i >= 0; i--)
	{
		out << ChangeSentence::to_low(this->GetIsWordPalindrome()[i].get_word()) << " ";
	}
	out << (this->GetIsWordSetPalindrome() ? " - y" : " - n") << endl << endl;

	return out;
}
