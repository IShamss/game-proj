#include "Alexandria.h"
#include<string>

int Alexandria::CardPrice = 0;
int Alexandria::feesTopay = 0;
Player* Alexandria::owner = NULL;
bool Alexandria::isinitialize = false;
bool Alexandria::bought = false;
Player* Alexandria::Mortgagedto = NULL;
Player* Alexandria::BenefitTo = NULL;
int Alexandria::BenefitTurns = -1;
int Alexandria::count = 0;

Alexandria::Alexandria(const CellPosition& pos) :Card(pos)
{
	cardNumber = 8;
	Upformortgage = NULL;
}

void Alexandria::setparameters()
{
	isinitialize = false;
}

void Alexandria::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (isinitialize == false)
	{
		pOut->PrintMessage("New Card Alexandria: Please enter the CardPrice");
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

void Alexandria::Apply(Grid* pGrid, Player* pPlayer)
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
			BenefitTo = pPlayer;
			pPlayer->SetWallet(pPlayer->GetWallet() - CardPrice);

			bought = true;

		}

		else if ((s == "Y" || "y") && pPlayer->GetWallet() < CardPrice)
		{
			pOut->PrintMessage("Sorry You don't have enough money in your Wallet to buy the Cell");
		}

		pGrid->ApplyforsameAlex(this);
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
int Alexandria::GetPrice() {
	return CardPrice;
}
Alexandria::~Alexandria(void)
{
}

void Alexandria::Setbought(bool x)
{
	bought = x;
}

bool Alexandria::Getbought()
{
	return bought;
}

void Alexandria::ApplyforAlex(Alexandria* org, Alexandria* copy)
{
	copy->owner = org->owner;
	copy->Setbought(org->Getbought());
	copy->Upformortgage = org->Upformortgage;
	copy->Mortgagedto = org->Mortgagedto;
}
void Alexandria::SetCardParameters(int price, int fees) {
	this->CardPrice = price;
	this->feesTopay = fees;
}
void Alexandria::SaveToFile(ofstream& output, int obj) {
	Card::SaveToFile(output, obj);
	output << " " << this->CardPrice << " " << this->feesTopay << std::endl;
}