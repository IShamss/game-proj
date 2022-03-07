#include "Luxor.h"
#include<string>

int Luxor::CardPrice = 0;
int Luxor::feesTopay = 0;
Player* Luxor::owner = NULL;
bool Luxor::isinitialize = false;
bool Luxor::bought = false;
Player* Luxor::Mortgagedto = NULL;
Player* Luxor::BenefitTo = NULL;
int Luxor::BenefitTurns = -1;
int Luxor::count = 0;

Luxor::Luxor(const CellPosition& pos) :Card(pos)
{
	cardNumber = 10;
	Upformortgage = NULL;
}

void Luxor::setparameters()
{
	isinitialize = false;
}

void Luxor::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (isinitialize == false)
	{
		pOut->PrintMessage("New Card Luxor: Please enter the CardPrice");
		CardPrice = pIn->GetInteger(pOut);
		pOut->PrintMessage("Please enter the Fees");
		feesTopay = pIn->GetInteger(pOut);
		isinitialize = true;
	}
	while (CardPrice < 0 || feesTopay < 0)
	{
		pGrid->PrintErrorMessage("Invalid value. Enter postitve values ...");
		pOut->PrintMessage("Please enter the CardPrice");
		CardPrice = pIn->GetInteger(pOut);
		pOut->PrintMessage("Please enter the Fees");
		feesTopay = pIn->GetInteger(pOut);
	}

	pOut->ClearStatusBar();
}

void Luxor::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();


	if (!bought)
	{
		pOut->PrintMessage("Do you want to buy this Cell?Y/N");
		string s = pIn->GetString(pOut);
		if ((s == "Y" || s == "y") && pPlayer->GetWallet() > CardPrice)
		{
			owner = pPlayer;
			Mortgagedto = pPlayer;
			pPlayer->SetWallet(pPlayer->GetWallet() - CardPrice);

			bought = true;

		}

		else if ((s == "Y" || "y") && pPlayer->GetWallet() < CardPrice)
		{
			pOut->PrintMessage("Sorry You don't have enough money in your Wallet to buy the Cell");
		}

		pGrid->ApplyforsameLuxor(this);
	}
	if (bought)
	{

		if (count <= BenefitTurns)
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - feesTopay);
			BenefitTo->SetWallet(BenefitTo->GetWallet() + feesTopay);
			count++;
		}
		else if (pPlayer == owner)
		{
			if (Mortgagedto != NULL)
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - feesTopay);
				Mortgagedto->SetWallet(Mortgagedto->GetWallet() + feesTopay);
			}
		}
		else
		{
			if (Mortgagedto != NULL)
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - feesTopay);
				Mortgagedto->SetWallet(Mortgagedto->GetWallet() + feesTopay);
			}
			else
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - feesTopay);
				owner->SetWallet(owner->GetWallet() + feesTopay);
			}
		}
		if (count == BenefitTurns)
		{
			BenefitTo = owner;
		}
	}
}
int Luxor::GetPrice() {
	return CardPrice;
}
Luxor::~Luxor(void)
{
}

void Luxor::Setbought(bool x)
{
	bought = x;
}

bool Luxor::Getbought()
{
	return bought;
}

void Luxor::ApplyforLuxor(Luxor* org, Luxor* copy)
{
	copy->owner = org->owner;
	copy->Setbought(org->Getbought());
	copy->Upformortgage = org->Upformortgage;
	copy->Mortgagedto = org->Mortgagedto;
}
void Luxor::SetCardParameters(int price, int fees) {
	this->CardPrice = price;
	this->feesTopay = fees;
}

void Luxor::SaveToFile(ofstream& output, int obj) {
	Card::SaveToFile(output, obj);
	output << " " << this->CardPrice << " " << this->feesTopay << std::endl;
}