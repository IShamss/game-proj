#pragma once
#include "Card.h"

#include <fstream>
class Aswan :public Card
{
	static bool isinitialize;
	static int CardPrice;
	static int feesTopay;

public:
	static Player* MortgagedTo;
	static Player* owner;
	static Player* BenefitTo;
	static int BenefitTurns;
	static int count;
	bool Upformortgage;
	static bool bought;

	Aswan(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);

	void setparameters();
	void SetCardParameters(int, int);

	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	static int GetPrice();
	virtual ~Aswan();

	void Setbought(bool x);
	bool Getbought();

	void ApplyforAswan(Aswan* org, Aswan* copy);
	virtual void SaveToFile(ofstream&, int);
};