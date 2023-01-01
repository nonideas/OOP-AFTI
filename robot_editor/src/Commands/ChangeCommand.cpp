#include <iterator>
#include <memory>
#include "ChangeCommand.h"

ChangeCommand::ChangeCommand(const std::uint64_t& _start, const std::uint64_t& _stop, const std::vector<std::string>& _changableLines)
	: start(_start), stop(_stop), changableLines(_changableLines) { };

void ChangeCommand::Execute(TextObject& textObject)
{
	std::copy(textObject.getLines().begin() + start, textObject.getLines().begin() + stop, std::back_inserter(bufferOnUndo));
	textObject.deleteLines(start, stop);
	textObject.addLines(start, changableLines);
}

void ChangeCommand::Undo(TextObject& textObject)
{
	textObject.deleteLines(start, start + changableLines.size());
	textObject.addLines(start, bufferOnUndo);
}
