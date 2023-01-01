#pragma once
#include "AbstractCommand.h"

class ChangeCommand final : public AbstractCommand
{
private:
	std::uint64_t start;
	std::uint64_t stop;
	std::vector<std::string> changableLines;
	std::vector<std::string> bufferOnUndo;

public:
	ChangeCommand(const std::uint64_t& _start, const std::uint64_t& _stop, const std::vector<std::string>& _changableLines);

	~ChangeCommand() = default;

	void Execute(TextObject& textObject) override;
	void Undo(TextObject& textObject) override;
};

