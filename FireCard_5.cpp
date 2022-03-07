#include "FireCard_5.h"
#include<iostream>
using namespace std;
//done by noha
FireCard_5::FireCard_5(const CellPosition& pos) : Card(pos)
{
	cardNumber = 5;
}

FireCard_5::~FireCard_5(void)
{
}

void FireCard_5::ReadCardParameters(Grid* pGrid)
{


	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();

	ptrOUT->PrintMessage("New FireCard-5...");
	c = pGrid->GetCurrentPlayer()->GetCell()->GetCellPosition();

	ptrIN->GetCellClicked();

	ptrOUT->ClearStatusBar();
}

void FireCard_5::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->firing(pPlayer);

}

