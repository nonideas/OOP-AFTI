#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Client.h"

std::stringstream ConvertFstreamToSstream(const std::string& _pathToReadFile)
{
	std::ifstream ifstream(_pathToReadFile);
	if (!ifstream.is_open()) {
		throw new std::exception("Enter correct path to files");
	}
	std::stringstream stream;
	stream << ifstream.rdbuf();
	return stream;
}


int main(int argc, char* argv[])
{
	try {
		std::stringstream text = ConvertFstreamToSstream("src/TextAndCommands/text1.txt");
		std::stringstream commands = ConvertFstreamToSstream("src/TextAndCommands/cmd1.txt");
		Client client(commands, text);
		std::cout << client.RunClient();
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}
