#include "BenefitAllCard.h"
#include "Cairo.h"
#include "Alexandria.h"
#include"Aswan.h"
#include "Hurghada.h"
#include"Luxor.h"
BenefitAllCard::BenefitAllCard(const CellPosition& pos) :Card(pos)
{
	cardNumber = 15;
}

void BenefitAllCard::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("New Benefit All Card, please enter number of turns..");
	pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}
void BenefitAllCard::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	//Player* p1;
	//Player* p2;
	//Player* p3;
	//Player* p4;
	//Player* p5;

	if (Cairo::bought == true) {
		Cairo::BenefitTo = pPlayer;
		Cairo::BenefitTurns = NumberOfTurns;
		Cairo::count = 0;
	}
	if (Alexandria::bought == true) {
		Alexandria::BenefitTo = pPlayer;
		Alexandria::BenefitTurns = NumberOfTurns;
		Alexandria::count = 0;
	}
	if (Aswan::bought == true) {
		Aswan::BenefitTo = pPlayer;
		Aswan::BenefitTurns = NumberOfTurns;
		Aswan::count = 0;
	}
	if (Luxor::bought == true) {
		Luxor::BenefitTo = pPlayer;
		Luxor::BenefitTurns = NumberOfTurns;
		Luxor::count = 0;
	}
	if (Hurghada::bought == true) {
		Hurghada::BenefitTo = pPlayer;
		Hurghada::BenefitTurns = NumberOfTurns;
		Hurghada::count = 0;
	}

}
BenefitAllCard:: ~BenefitAllCard() {

}