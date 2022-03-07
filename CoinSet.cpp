#include "CoinSet.h"
#include "Player.h"
#include<iostream>
#include <fstream>
using namespace std;
//done by (noha)
void CoinSet::setAmount(int c) {
	amount = c;
}
int CoinSet::getAmount() {
	return amount;
}
void CoinSet::Draw(Output* pOut)const {
	pOut->DrawCoinSet(position);
}
void CoinSet::Apply(Grid* pGrid, Player* pPlayer) {
	pPlayer->SetWallet(amount+pPlayer->GetWallet());
	pGrid->UpdateInterface();
}

CoinSet::CoinSet(int x, CellPosition pos) : GameObject(pos)
{
	amount = x;
}

void CoinSet::SetPosition(CellPosition cpos)
{
	position = cpos;
}

void CoinSet::SaveToFile(ofstream& output, int obj) {
	if (obj == 4) {
		GameObject::SaveToFile(output, obj);
		int amount = this->getAmount();
		output << " " << amount << std::endl;
	}
}
void CoinSet::getCoinPtr(int num, ifstream& inputFile, Grid* newGrid) {
	int i = 0;
	while (i < num) {
		int cellNum, amount;
		inputFile >> cellNum >> amount;

		CoinSet* newCoin = new CoinSet(amount, CellPosition(cellNum));
		newGrid->AddObjectToCell(newCoin);
		i++;
	}
}