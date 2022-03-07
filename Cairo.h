#pragma once
#include "Card.h"
#include <fstream>
class Cairo :public Card
{
	static bool isinitialize;
	static int CardPrice;
	static int feesTopay;



public:
	static Player* Mortgagedto;
	static Player* owner;
	static Player* BenefitTo;
	static int BenefitTurns;
	static int count;
	static bool Upformortgage;
	static bool bought;

	Cairo(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	void setparameters();
	void SetCardParameters(int, int);
	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	static int GetPrice();
	//void SetOwner(Player* P);
	void ApplyforCairo(Cairo* org, Cairo* copy);
	virtual ~Cairo();
	void Setbought(bool x);
	bool Getbought();
	virtual void SaveToFile(ofstream&, int);
};

