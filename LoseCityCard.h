#pragma once
#include "Card.h"
class LoseCityCard :
	public Card
{
public:
	LoseCityCard(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~LoseCityCard();
};


