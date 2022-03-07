#include "Hurghada.h"
#include<string>

int Hurghada::CardPrice = 0;
int Hurghada::feesTopay = 0;
Player* Hurghada::owner = NULL;
bool Hurghada::isinitialize = false;
bool Hurghada::bought = false;
Player* Hurghada::Mortgagedto = NULL;
Player* Hurghada::BenefitTo = NULL;
int Hurghada::BenefitTurns = -1;
int Hurghada::count = 0;

Hurghada::Hurghada(const CellPosition& pos) :Card(pos)
{
	cardNumber = 11;
	Upformortgage = NULL;
}

void Hurghada::setparameters()
{
	isinitialize = false;
}

void Hurghada::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (isinitialize == false)
	{
		pOut->PrintMessage("New Card Hurghada: Please enter the CardPrice");
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

void Hurghada::Apply(Grid* pGrid, Player* pPlayer)
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

		pGrid->ApplyforsameHurg(this);
	}
	if (bought)
	{

		if (BenefitTo != owner)
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
int Hurghada::GetPrice() {
	return CardPrice;
}
Hurghada::~Hurghada(void)
{
}
void Hurghada::SetCardParameters(int price, int fees) {
	this->CardPrice = price;
	this->feesTopay = fees;
}
void Hurghada::Setbought(bool x)
{
	bought = x;
}

bool Hurghada::Getbought()
{
	return bought;
}

void Hurghada::ApplyforHurg(Hurghada* org, Hurghada* copy)
{
	copy->owner = org->owner;
	copy->Setbought(org->Getbought());
	copy->Upformortgage = org->Upformortgage;
	copy->Mortgagedto = org->Mortgagedto;
}

void Hurghada::SaveToFile(ofstream& output, int obj) {
	Card::SaveToFile(output, obj);
	output << " " << this->CardPrice << " " << this->feesTopay << std::endl;
}