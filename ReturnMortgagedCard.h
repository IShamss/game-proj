#pragma once
#include "Card.h"
class ReturnMortgagedCard :
	public Card
{
public:
	ReturnMortgagedCard(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~ReturnMortgagedCard();
};

