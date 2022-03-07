#pragma once
#include "Card.h"
#include <fstream>
class Alexandria :public Card
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
	bool Upformortgage;
	static bool bought;

	Alexandria(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);
	void setparameters();

	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	static int GetPrice();
	virtual ~Alexandria();

	void Setbought(bool x);
	bool Getbought();

	void ApplyforAlex(Alexandria* org, Alexandria* copy);
	virtual void SaveToFile(ofstream&, int);
	void SetCardParameters(int, int);
};