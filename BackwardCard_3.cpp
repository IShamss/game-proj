#include "BackwardCard_3.h"
//done by noha

BackwardCard_3::BackwardCard_3(const CellPosition& pos) : Card(pos) 
{
	cardNumber = 3; 
}

BackwardCard_3::~BackwardCard_3(void)
{
}

void BackwardCard_3::ReadCardParameters(Grid* pGrid)
{


	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();
	 
	ptrOUT->PrintMessage("New BackWardCard-3...");
	DiceValue = pGrid->GetCurrentPlayer()->GetDiceValue();
	
	ptrIN->GetCellClicked();
	
	ptrOUT->ClearStatusBar();
}

void BackwardCard_3::Apply(Grid* pGrid, Player* pPlayer)
{

	
	Card::Apply(pGrid, pPlayer);
	pGrid->MovePlayersBackWard(pPlayer);
}
