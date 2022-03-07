#pragma once
#include "Action.h"

class InputDice :public Action
{
	int dicenumber;

public:

	InputDice(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~InputDice();
};
