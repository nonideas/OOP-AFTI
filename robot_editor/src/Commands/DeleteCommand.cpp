#include <iterator>
#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(const std::uint64_t& _start, const std::uint64_t& _stop) 
	: start(_start), stop(_stop) {}


void DeleteCommand::Execute(TextObject& textObject)
{
	std::copy(textObject.getLines().begin() + start, textObject.getLines().begin() + stop, std::back_inserter(bufferOnUndo));
	textObject.deleteLines(start, stop);
}

void DeleteCommand::Undo(TextObject& textObject)
{
	textObject.addLines(start, bufferOnUndo);
}