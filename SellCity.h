#pragma once
#include "Action.h"
#include "CellPosition.h"

class SellCity :public Action
{
	CellPosition Cpos;
public:

	SellCity(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~SellCity();

};