#include "ReturnMortgagedCard.h"
#include"Cairo.h"
#include "Alexandria.h"
#include"Aswan.h"
#include "Hurghada.h"
#include"Luxor.h"
ReturnMortgagedCard::ReturnMortgagedCard(const CellPosition& pos) :Card(pos)
{
	cardNumber = 14;
}
void ReturnMortgagedCard::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pGrid->PrintErrorMessage("New ReturnMortgagedCard .....");
	pOut->ClearStatusBar();
}
void ReturnMortgagedCard::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	int min = 999999999;
	if (Cairo::owner == pPlayer && Cairo::Mortgagedto != pPlayer) {
		if (Cairo::GetPrice() < min) {
			min = Cairo::GetPrice();
		}
	}
	if (Alexandria::owner == pPlayer && Alexandria::Mortgagedto != pPlayer) {
		if (Alexandria::GetPrice() < min) {
			min = Alexandria::GetPrice();
		}
	}
	if (Aswan::owner == pPlayer && Aswan::MortgagedTo != pPlayer) {
		if (Aswan::GetPrice() < min) {
			min = Aswan::GetPrice();
		}
	}
	if (Luxor::owner == pPlayer && Luxor::Mortgagedto != pPlayer) {
		if (Luxor::GetPrice() < min) {
			min = Luxor::GetPrice();
		}
	}
	if (Hurghada::owner == pPlayer && Hurghada::Mortgagedto != pPlayer) {
		if (Hurghada::GetPrice() < min) {
			min = Hurghada::GetPrice();
		}
	}
	if (Cairo::GetPrice() == min) {
		if (Cairo::owner != Cairo::Mortgagedto) {
			Cairo::Mortgagedto = Cairo::owner;
		}

	}
	if (Alexandria::GetPrice() == min) {
		if (Alexandria::owner != Alexandria::Mortgagedto) {
			Alexandria::Mortgagedto = Alexandria::owner;
		}

	}
	if (Aswan::GetPrice() == min) {
		if (Aswan::owner != Aswan::MortgagedTo) {
			Aswan::MortgagedTo = Aswan::owner;
		}

	}
	if (Luxor::GetPrice() == min) {
		if (Luxor::owner != Luxor::Mortgagedto) {
			Luxor::Mortgagedto = Luxor::owner;
		}

	}
	if (Hurghada::GetPrice() == min) {
		if (Hurghada::owner != Hurghada::Mortgagedto) {
			Hurghada::Mortgagedto = Hurghada::owner;
		}

	}

}
ReturnMortgagedCard::~ReturnMortgagedCard() {
}