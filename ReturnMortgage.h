#include "Action.h"
#include "CellPosition.h"

class Return_Mortgage :public Action
{
	CellPosition Cpos;

public:

	Return_Mortgage(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	~Return_Mortgage();
};
