#include "Client.h"

Client::Client(std::istream& commandStream, std::istream& textStream) :
	textEditor(TextEditor(commandStream, textStream)) { }

std::string Client::RunClient()
{
	return textEditor.Run();
}
