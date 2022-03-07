#pragma once
#include "Action.h"
#include <string>
class SaveGridAction :public Action {
	string fname;
public:
	SaveGridAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SaveGridAction();
};

//Mohamed Shams
