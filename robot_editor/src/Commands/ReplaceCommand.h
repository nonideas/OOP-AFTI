#pragma once
#include "AbstractCommand.h"

class ReplaceCommand final : public AbstractCommand
{
private:
	std::uint64_t start;
	std::uint64_t stop;
	std::vector<std::string> linesToDelete;
	std::vector<std::string> linesToAdd;
	std::uint64_t posLinesToDelete;

public:
	ReplaceCommand(const std::uint64_t& _start, const std::uint64_t& _stop,
		const std::vector<std::string>& _linesToDelete, const std::vector<std::string>& _linesToAdd);

	~ReplaceCommand() = default;

	void Execute(TextObject& textObject) override;
	void Undo(TextObject& textObject) override;

private:
	bool serachTextInTextObject(TextObject& textObject);
};

