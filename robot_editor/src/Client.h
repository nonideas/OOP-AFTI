#pragma once
#include "TextEditor.h"

class Client final
{
private:
	TextEditor textEditor;

public:
	Client(std::istream& commandStream, std::istream& textStream);

	std::string RunClient();
};

