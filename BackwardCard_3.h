#pragma once

#include "Card.h"
//done by noha
class BackwardCard_3 : public Card
{
	
	int DiceValue; 

public:
	BackwardCard_3(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);  

	virtual void Apply(Grid* pGrid, Player* pPlayer);  

	virtual ~BackwardCard_3();
};


