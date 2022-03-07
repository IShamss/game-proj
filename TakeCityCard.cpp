#include "TakeCityCard.h"
#include "Cairo.h"
#include"Alexandria.h"
#include"Aswan.h"
#include"Hurghada.h"
#include"Luxor.h"
TakeCityCard::TakeCityCard(const CellPosition& pos) : Card(pos) {
	cardNumber = 12;
}
void TakeCityCard::ReadCardParameters(Grid* pGrid) {
	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();
	pGrid->PrintErrorMessage("New TakeCityCard ...");
	ptrOUT->ClearStatusBar();
}

void TakeCityCard::Apply(Grid* pGrid, Player* pPlayer)
{
	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();
	ptrOUT->PrintMessage("Type City Name...");
	CityName = ptrIN->GetString(ptrOUT);
	ptrOUT->ClearStatusBar();

	Card::Apply(pGrid, pPlayer);
	if (CityName == "Cairo" || CityName == "cairo") {
		Cairo::owner = pPlayer;
	}
	if (CityName == "Alex" || CityName == "alex") {
		Alexandria::owner = pPlayer;
	}
	if (CityName == "Aswan" || CityName == "aswan") {
		Aswan::owner = pPlayer;
	}
	if (CityName == "Hurghada" || CityName == "hurghada") {
		Hurghada::owner = pPlayer;
	}
	if (CityName == "Luxor" || CityName == "luxor") {
		Luxor::owner = pPlayer;
	}
}
TakeCityCard::~TakeCityCard() {

}