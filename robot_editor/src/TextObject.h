#pragma once
#include <string>
#include <vector>

class TextObject
{
protected:
	std::vector<std::string> Lines;

public:
	TextObject(std::istream& textStream);

	void deleteLines(const std::uint64_t& start, const std::uint64_t& stop);
	void addLines(const std::uint64_t& start, const std::vector<std::string>& bufferOnUndo);

	const std::vector<std::string>& getLines() const {
		return Lines;
	}
};

