#pragma once

#include "Action.h"

class ToPlayMode : public Action
{
	bool decisiontosave;
public:
	ToPlayMode(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~ToPlayMode();
};
