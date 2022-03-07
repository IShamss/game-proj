#include "Action.h"
#include "CellPosition.h"

class Accept_Mortgage :public Action
{
	CellPosition Cpos;
public:

	Accept_Mortgage(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~Accept_Mortgage();
};
