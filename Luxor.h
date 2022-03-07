#pragma once
#include "Card.h"
#include <fstream>
class Luxor :public Card
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

	Luxor(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid);
	void setparameters();

	virtual  void Apply(Grid* pGrid, Player* pPlayer);
	static int GetPrice();
	virtual ~Luxor();

	bool Getbought();
	void Setbought(bool x);

	void ApplyforLuxor(Luxor* org, Luxor* copy);
	virtual void SaveToFile(ofstream&, int);
	void SetCardParameters(int, int);

};