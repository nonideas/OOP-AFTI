#include <algorithm>
#include <iterator>
#include <memory>
#include <regex>
#include "ReplaceCommand.h"

bool ReplaceCommand::serachTextInTextObject(TextObject& textObject)
{
	for (std::uint64_t i = start; i < stop - linesToDelete.size(); i++)
	{
		for (std::uint64_t j = 0; j < linesToDelete.size(); j++)
		{
			if (textObject.getLines()[i + j] != linesToDelete[j]) {
				break;
			}
			if (j == linesToDelete.size() - 1) {
				posLinesToDelete = i;
				return true;
			}
		}
	}
	return false;
}

ReplaceCommand::ReplaceCommand(const std::uint64_t& _start, const std::uint64_t& _stop,
	const std::vector<std::string>& _linesToDelete, const std::vector<std::string>& _linesToAdd) 
	: start(_start), stop(_stop), linesToDelete(_linesToDelete), linesToAdd(_linesToAdd) { }


void ReplaceCommand::Execute(TextObject& textObject)
{
	if (serachTextInTextObject(textObject)) {
		textObject.deleteLines(posLinesToDelete, posLinesToDelete + linesToDelete.size());
		textObject.addLines(posLinesToDelete, linesToAdd);
	}
	else {
		throw new std::exception("no match text");
	}
}

void ReplaceCommand::Undo(TextObject& textObject)
{
	textObject.deleteLines(posLinesToDelete, posLinesToDelete + linesToAdd.size());
	textObject.addLines(posLinesToDelete, linesToDelete);
}
