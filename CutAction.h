#pragma once
#include "Action.h"
#include"CellPosition.h"

class CutAction : public Action {
	//int type; // specifies whether the object to be copied is a card or a coinSet
	//int cardNum;
	//int coinSetAmount;
	CellPosition source;
public:
	CutAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

	virtual ~CutAction();
};

//Mohamed Shams