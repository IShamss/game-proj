#pragma once
#include "Action.h"
#include "Cell.h"
#include "CellPosition.h"
class Delete : public Action
{
	CellPosition Cpos;
public:

	Delete(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads cellpostion parameter 

	virtual void Execute(); // delete object if exists in cell 
							

};
