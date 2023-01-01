#include <iostream>
#include <fstream>
#include <sstream>
#include "TextObject.h"

TextObject::TextObject(std::istream& textStream)
{
	std::string line;

	while (std::getline(textStream, line))
	{
		if (!line.empty()) {
			Lines.push_back(line);
		}
	}
}

void TextObject::addLines(const std::uint64_t& start, const std::vector<std::string>& bufferOnUndo)
{
	Lines.insert(Lines.begin() + start, bufferOnUndo.begin(), bufferOnUndo.end());
}

void TextObject::deleteLines(const std::uint64_t& start, const std::uint64_t& stop)
{
	Lines.erase(Lines.begin() + start, Lines.begin() + stop);
}
