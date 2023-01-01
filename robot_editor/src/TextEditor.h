#pragma once
#include <memory>
#include <vector>
#include <stack>
#include "Commands/AbstractCommand.h"

class TextEditor final
{
private:
	std::vector<std::string> commandLines;
	std::stack<std::unique_ptr<AbstractCommand>> commandHistory;
	std::stack<std::unique_ptr<AbstractCommand>> redoCommandHistory;
	TextObject textObject;

public:
	TextEditor(std::istream& commandStream, std::istream& textStream);

	std::string Run();

private:
	void Undo();
	void Redo();
};

