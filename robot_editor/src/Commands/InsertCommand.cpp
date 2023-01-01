#include "InsertCommand.h"

InsertCommand::InsertCommand(const std::uint64_t& _start, const std::vector<std::string>& _insertLines)
	: start(_start), insertLines(_insertLines) { }

void InsertCommand::Execute(TextObject& textObject)
{
	textObject.addLines(start, insertLines);
}

void InsertCommand::Undo(TextObject& textObject)
{
	textObject.deleteLines(start, start + insertLines.size());
}
