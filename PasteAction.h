#pragma once
#include "Action.h"
#include "CellPosition.h"
#include "Grid.h"

class PasteAction : public Action {
	CellPosition destination;
public:
	PasteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~PasteAction();
};
