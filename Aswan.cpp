#include "Aswan.h"
#include<string>

int Aswan::CardPrice = 0;
int Aswan::feesTopay = 0;
Player* Aswan::owner = NULL;
bool Aswan::isinitialize = false;
bool Aswan::bought = false;
Player* Aswan::MortgagedTo = NULL;
Player* Aswan::BenefitTo = NULL;
int Aswan::BenefitTurns = -1;
int Aswan::count = 0;

Aswan::Aswan(const CellPosition& pos) :Card(pos)
{
	cardNumber = 9;
	Upformortgage = NULL;
}

void Aswan::setparameters()
{
	isinitialize = false;
}

void Aswan::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (isinitialize == false)
	{
		pOut->PrintMessage("New Card Aswan: Please enter the CardPrice");
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

void Aswan::Apply(Grid* pGrid, Player* pPlayer)
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
			MortgagedTo = pPlayer;
			pPlayer->SetWallet(pPlayer->GetWallet() - CardPrice);

			bought = true;

		}

		else if ((s == "Y" || "y") && pPlayer->GetWallet() < CardPrice)
		{
			pOut->PrintMessage("Sorry You don't have enough money in your Wallet to buy the Cell");
		}

		pGrid->ApplyforsameAswan(this);
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
			if (MortgagedTo != NULL)
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - feesTopay);
				MortgagedTo->SetWallet(MortgagedTo->GetWallet() + feesTopay);
			}
		}
		else
		{
			if (MortgagedTo != NULL)
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - feesTopay);
				MortgagedTo->SetWallet(MortgagedTo->GetWallet() + feesTopay);
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
int Aswan::GetPrice() {
	return CardPrice;
}
Aswan::~Aswan(void)
{
}

void Aswan::Setbought(bool x)
{
	bought = x;
}

bool Aswan::Getbought()
{
	return bought;
}

void Aswan::ApplyforAswan(Aswan* org, Aswan* copy)
{
	copy->owner = org->owner;
	copy->Setbought(org->Getbought());
	copy->Upformortgage = org->Upformortgage;
	copy->MortgagedTo = org->MortgagedTo;
}
void Aswan::SetCardParameters(int price, int fees) {
	this->CardPrice = price;
	this->feesTopay = fees;
}
void Aswan::SaveToFile(ofstream& output, int obj) {
	Card::SaveToFile(output, obj);
	output << " " << this->CardPrice << " " << this->feesTopay << std::endl;
}