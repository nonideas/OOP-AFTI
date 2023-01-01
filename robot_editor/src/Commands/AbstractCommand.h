#pragma once
#include "../TextObject.h"

class AbstractCommand
{
public:
	virtual void Execute(TextObject& textObject) = 0;
	virtual void Undo(TextObject& textObject) = 0;

	virtual ~AbstractCommand() = default;
};