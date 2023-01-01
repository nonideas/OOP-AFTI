#include <iostream>
#include <fstream>
#include <sstream>
#include "TextEditor.h"
#include "CommandFactory.h"

TextEditor::TextEditor(std::istream& commandStream, std::istream& textStream) :
	textObject(TextObject(textStream))
{
	std::string line;

	while (std::getline(commandStream, line))
	{
		commandLines.push_back(line);
	}
};

std::string TextEditor::Run()
{
	for (const auto& str : commandLines)
	{
		if (str == "undo")
		{
			Undo();
			continue;
		}
		if (str == "redo")
		{
			Redo();
			continue;
		}
		std::unique_ptr<AbstractCommand> command = CommandFactory::CommandCreator(str, textObject);
		command->Execute(textObject);
		commandHistory.push(std::move(command));
		while (!redoCommandHistory.empty()) {
			redoCommandHistory.pop();
		}
	}
	std::string text;
	for (const auto& line : textObject.getLines()) {
		text += line + "\n";
	}
	return text;
}

void TextEditor::Undo()
{
	commandHistory.top()->Undo(textObject);
	redoCommandHistory.push(std::move(commandHistory.top()));
	commandHistory.pop();
}

void TextEditor::Redo()
{
	redoCommandHistory.top()->Execute(textObject);
	commandHistory.push(std::move(redoCommandHistory.top()));
	redoCommandHistory.pop();
}

