#pragma once
#include "AbstractCommand.h"

class InsertCommand final : public AbstractCommand
{
private:
	std::uint64_t start;
	std::vector<std::string> insertLines;

public:
	InsertCommand(const std::uint64_t& _start, const std::vector<std::string>& _insertLines);

	~InsertCommand() = default;

	void Execute(TextObject& textObject) override;
	void Undo(TextObject& textObject) override;
};

