#pragma once
#pragma once
#include "Action.h"
#include "CellPosition.h"

class Offer_Mortgage :public Action
{
private:
	CellPosition Cpos;
public:

	Offer_Mortgage(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~Offer_Mortgage();

};
