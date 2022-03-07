#pragma once
#include "Card.h"
class BenefitAllCard :
	public Card
{
	int NumberOfTurns;
public:
	BenefitAllCard(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~BenefitAllCard();
};


