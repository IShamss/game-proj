#include "PreventCard_4.h"
#include<iostream>
//done by noha
using namespace std;
PreventCard_4::PreventCard_4(const CellPosition& pos) : Card(pos)
{
	cardNumber = 4;
}

PreventCard_4::~PreventCard_4(void)
{
}

void PreventCard_4::ReadCardParameters(Grid* pGrid)
{


	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();

	ptrOUT->PrintMessage("New PreventCard_4...");
	//c1 = ptrIN->GetCellClicked();



	ptrOUT->ClearStatusBar();
}

void PreventCard_4::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();
	ptrOUT->PrintMessage("Choose Player");
	c1 = ptrIN->GetCellClicked();
	Player* otherp;
	otherp = pGrid->GetClickedPlayer(c1);
	otherp->IsChosen();



}

