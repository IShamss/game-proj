#pragma once
#include"Card.h"
//done by noha
class NextCard_2:public Card
{
	int type;

public:
	NextCard_2(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual ~NextCard_2();


};

