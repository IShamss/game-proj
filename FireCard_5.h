#pragma once
#include"Card.h"
//done by noha
class FireCard_5:public Card
{
	CellPosition c;
   

public:
	FireCard_5(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual ~FireCard_5();
};

