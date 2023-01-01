#pragma once
#include "../TextObject.h"
#include "AbstractCommand.h"

class DeleteCommand final : public AbstractCommand
{
private:
	std::uint64_t start;
	std::uint64_t stop;
	std::vector<std::string> bufferOnUndo;

public:
	DeleteCommand( const std::uint64_t& _start, const std::uint64_t& _stop);

	~DeleteCommand() = default;

	void Execute(TextObject& textObject) override;
	void Undo(TextObject& textObject) override;
};



