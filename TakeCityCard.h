#pragma once
#include "Card.h"
class TakeCityCard: public Card
{
	string CityName;
public:
	TakeCityCard(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer);

	virtual ~TakeCityCard();
};

