#pragma once
#include "Action.h"
#include"CellPosition.h"

class CopyAction : public Action {
	//int type; // specifies whether the object to be copied is a card or a coinSet
	int cardNum;
	//int coinSetAmount;
	CellPosition source;
public:
	CopyAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~CopyAction();
};

//Mohamed Shams