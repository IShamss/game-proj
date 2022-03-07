#include "FreezeCard.h"
void FreezeCard::ReadCardParameters(Grid* pGrid)
{
	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();
	ptrOUT->PrintMessage("New FreezeCard: Enter its turns ...");
	numberTurns = ptrIN->GetInteger(ptrOUT);
	ptrOUT->PrintMessage("Freeze the even cells? (Y/N) ");
	string S = ptrIN->GetString(ptrOUT);
	if (S == "Y" || S == "y") {
		isEven = true;
	}
	else {
		isEven = false;
	}
	ptrOUT->ClearStatusBar();
}
void FreezeCard::Apply(Grid* pGrid, Player* pPlayer) {
	Card::Apply(pGrid, pPlayer);
	pGrid->FreezePlayers(pPlayer, isEven, numberTurns);
}
FreezeCard::FreezeCard(const CellPosition& pos) :Card(pos) {
	cardNumber = 6;
}
FreezeCard::~FreezeCard() {}