#pragma once
#include "Action.h"
#include "Grid.h"
#include "CoinSet.h"

class AddCoinSetAction :public Action {
	int amount;
	CellPosition cell;

public:
	AddCoinSetAction(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters(); 

	virtual void Execute(); 

	virtual ~AddCoinSetAction();
};

//Mohamed Shams