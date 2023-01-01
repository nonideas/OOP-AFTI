#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace ChangeSentence
{
	std::vector<std::string> separate_sentence(const std::string& sentence);
	std::string to_low(std::string word);
	std::string reverse_word(std::string word);
	std::string concatenation_words(const std::vector<std::string>& words);

}
