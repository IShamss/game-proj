#include "LoseCityCard.h"
#include"Cairo.h"
#include "Alexandria.h"
#include"Aswan.h"
#include "Hurghada.h"
#include"Luxor.h"
LoseCityCard::LoseCityCard(const CellPosition& pos) :Card(pos)
{
	cardNumber = 13;
}
void LoseCityCard::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pGrid->PrintErrorMessage("New LoseCityCard");
	pOut->ClearStatusBar();
}
void LoseCityCard::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	int max = 0;
	if (Cairo::owner == pPlayer) {
		if (Cairo::GetPrice() > max) {
			max = Cairo::GetPrice();
		}
	}
	if (Alexandria::owner == pPlayer) {
		if (Alexandria::GetPrice() > max) {
			max = Alexandria::GetPrice();
		}
	}
	if (Aswan::owner == pPlayer) {
		if (Aswan::GetPrice() > max) {
			max = Aswan::GetPrice();
		}
	}
	if (Luxor::owner == pPlayer) {
		if (Luxor::GetPrice() > max) {
			max = Luxor::GetPrice();
		}
	}
	if (Hurghada::owner == pPlayer) {
		if (Hurghada::GetPrice() > max) {
			max = Hurghada::GetPrice();
		}
	}
	if (Cairo::GetPrice() == max) {
		if (Cairo::owner == Cairo::Mortgagedto) {
			Cairo::owner = NULL;
			Cairo::Mortgagedto = NULL;
			Cairo::bought = false;
		}
		else {
			Cairo::owner = Cairo::Mortgagedto;
		}

	}
	if (Alexandria::GetPrice() == max) {
		if (Alexandria::owner == Alexandria::Mortgagedto) {
			Alexandria::owner = NULL;
			Alexandria::Mortgagedto = NULL;
			Alexandria::bought = false;
		}
		else {
			Alexandria::owner = Alexandria::Mortgagedto;
		}

	}
	if (Aswan::GetPrice() == max) {
		if (Aswan::owner == Aswan::MortgagedTo) {
			Aswan::owner = NULL;
			Aswan::MortgagedTo = NULL;
			Aswan::bought = false;
		}
		else {
			Aswan::owner = Aswan::MortgagedTo;
		}

	}
	if (Luxor::GetPrice() == max) {
		if (Luxor::owner == Luxor::Mortgagedto) {
			Luxor::owner = NULL;
			Luxor::Mortgagedto = NULL;
			Luxor::bought = false;
		}
		else {
			Luxor::owner = Luxor::Mortgagedto;
		}

	}
	if (Hurghada::GetPrice() == max) {
		if (Hurghada::owner == Hurghada::Mortgagedto) {
			Hurghada::owner = NULL;
			Hurghada::Mortgagedto = NULL;
			Hurghada::bought = false;
		}
		else {
			Hurghada::owner = Hurghada::Mortgagedto;
		}

	}

}
LoseCityCard::~LoseCityCard() {
}



