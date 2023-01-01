#pragma once
#include <memory>
#include <stdexcept>
#include <utility>
#include "Commands/ChangeCommand.h"
#include "Commands/DeleteCommand.h"
#include "Commands/InsertCommand.h"
#include "Commands/ReplaceCommand.h"

class CommandFactory final
{
public:
	CommandFactory() = delete;
	static std::unique_ptr<AbstractCommand> CommandCreator(const std::string& paramLine, TextObject& textObj);

private:
	static std::vector<std::string> CommandParser(const std::string& commandLine);
	static std::vector<std::string> TextParser(std::string& textLine);

	static std::pair<std::uint64_t, std::uint64_t> GetIntervals(const std::vector<std::string>& command, TextObject& textObj);
	static std::string SeparateWords(const std::string& line, std::uint64_t& pos, const std::string& separate_characters);
};
