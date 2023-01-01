#include "CommandFactory.h"

std::vector<std::string> CommandFactory::CommandParser(const std::string& commandLine)
{
	std::uint64_t pos = 0;
	bool isBeginBracketText = false;
	std::string separateCharacters = " ";
	std::string textSeparateCharacters = "\"";
	std::string separator = separateCharacters;
	std::vector<std::string> lineSeparated = std::vector<std::string>();

	while (pos != std::string::npos)
	{
		if (pos == commandLine.size()) {
			break;
		}
		if (isBeginBracketText) {
			separator = separateCharacters;
			pos++;
			isBeginBracketText = false;
			continue;
		}
		if (commandLine[pos+1] == '\"') {
			pos += 1;
			separator = textSeparateCharacters;
			isBeginBracketText = true;
		}
		lineSeparated.push_back(SeparateWords(commandLine, pos, separator));
	}
	return lineSeparated;
}

void StringReplacer(std::string& textLine, const std::string& src, const std::string& dst)
{
	size_t pos = textLine.find(src);
	while (pos != std::string::npos) {
		textLine.replace(pos, src.size(), dst);
		pos = textLine.find(src, pos);
	}
}

std::vector<std::string> CommandFactory::TextParser(std::string& textLine)
{
	StringReplacer(textLine, "\\n", "\n");
	StringReplacer(textLine, "\\\\", "\\");
	std::uint64_t pos = 0;
	std::string separateCharacters = "\n";

	std::vector<std::string> lineSeparated = std::vector<std::string>();

	while (pos != std::string::npos)
	{
		lineSeparated.push_back(SeparateWords(textLine, pos, separateCharacters));
	}
	return lineSeparated;
}

std::unique_ptr<AbstractCommand> CommandFactory::CommandCreator(const std::string& paramLine, TextObject& textObj)
{
	std::vector<std::string> params = CommandParser(paramLine);
	std::pair<std::uint64_t, std::uint64_t> intervals = GetIntervals(params, textObj);
	if (params[0] == "delete")
	{
		return std::unique_ptr<DeleteCommand>(new DeleteCommand(intervals.first, intervals.second));
	}
	if (params[0] == "change")
	{
		return std::unique_ptr<ChangeCommand>(new ChangeCommand(intervals.first, intervals.second, TextParser(params.back())));
	}
	if (params[0] == "insert")
	{
		return std::unique_ptr<InsertCommand>(new InsertCommand(std::stoull(params[2]), TextParser(params[3])));
	}
	if (params[0] == "replace")
	{
		return std::unique_ptr<ReplaceCommand>(new ReplaceCommand(intervals.first, intervals.second,
			TextParser(params[params.size() - 3]), TextParser(params.back())));
	}
	else
	{
		throw new std::runtime_error("undefined parameter");
	}
}

std::pair<std::uint64_t, std::uint64_t> CommandFactory::GetIntervals(const std::vector<std::string>& command, TextObject& textObj)
{
	std::uint64_t start = 0;
	std::uint64_t stop = textObj.getLines().size();
	for (std::uint64_t i = 0; i < command.size(); i++)
	{
		if (command[i] == "from") {
			start = std::stoull(command[i + 1]);
		}
		if (command[i] == "to" && std::stoull(command[i + 1]) < stop) {
			stop = std::stoull(command[i + 1]);
		}
	}
	return std::make_pair(start, stop);
}

std::string CommandFactory::SeparateWords(const std::string& line, std::uint64_t& pos, const std::string& separate_characters)
{
	pos = line.find_first_not_of(separate_characters, pos);
	if (pos != std::string::npos) {
		uint64_t pos_end = line.find_first_of(separate_characters, pos);
		uint64_t len = (pos_end == std::string::npos) ? std::string::npos : pos_end - pos;

		std::string word(line.substr(pos, len));

		pos = pos_end;
		if (pos != std::string::npos) {
			if (line[pos - 1] == '\\' && separate_characters == "\"") {
				word += "\"" + SeparateWords(line, pos, separate_characters);
			}
		}
		return word;
	}
	return "";
}

