#pragma once
#include "Action.h"

class ToDesignMode : public Action
{
private:
	bool decisiontoswitch;
public:
	ToDesignMode(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	~ToDesignMode();
};