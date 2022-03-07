#pragma once
#include"Card.h"
#include"CellPosition.h"
//done by noha
class PreventCard_4:public Card
{
	CellPosition c1;

public:
	PreventCard_4(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual ~PreventCard_4();
};

