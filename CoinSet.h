#pragma once
#include"GameObject.h"
#include <fstream>
//done by (noha)
class CoinSet :public GameObject
{
	int amount;
public:
	CoinSet(int x, CellPosition pos);
	void setAmount(int c);
	int getAmount();
	void Draw(Output* pOut) const;
	void Apply(Grid* pGrid, Player* pPlayer);
	void SaveToFile(ofstream&, int);
	void SetPosition(CellPosition cpos);
	void getCoinPtr(int num, ifstream& inputFile, Grid* newGrid);
};

