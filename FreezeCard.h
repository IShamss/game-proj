#pragma once
#include "Card.h"
class FreezeCard :
	public Card
{
	bool isEven;
	int numberTurns;
public:
	FreezeCard(const CellPosition& pos);
	void ReadCardParameters(Grid* pGrid);

	void Apply(Grid* pGrid, Player* pPlayer);
	~FreezeCard();
};



