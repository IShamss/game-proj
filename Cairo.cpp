#include "Cairo.h"
#include<string>
int Cairo::CardPrice = 0;
int Cairo::feesTopay = 0;
Player* Cairo::owner = NULL;
bool Cairo::isinitialize = false;
bool Cairo::bought = false;
Player* Cairo::BenefitTo = NULL;
int Cairo::BenefitTurns = -1;
int Cairo::count = 0;
bool Cairo::Upformortgage = false;
Player* Cairo::Mortgagedto = NULL;

Cairo::Cairo(const CellPosition& pos) :Card(pos)
{
	cardNumber = 7;
}

void Cairo::setparameters()
{
	isinitialize = false;
}

void Cairo::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (isinitialize == false)
	{
		pOut->PrintMessage("New Card Cairo: Please enter the CardPrice");
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

void Cairo::Apply(Grid* pGrid, Player* pPlayer)
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

		pGrid->ApplyforsameCairo(this);
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
int Cairo::GetPrice() {
	return CardPrice;
}
//void Cairo::SetOwner(Player* P) {
	//owner = P;
//}
Cairo::~Cairo(void)
{

}

void Cairo::Setbought(bool x)
{
	bought = x;
}

bool Cairo::Getbought()
{
	return bought;
}

void Cairo::ApplyforCairo(Cairo* org, Cairo* copy)
{
	copy->owner = org->owner;
	copy->Setbought(org->Getbought());
	copy->Upformortgage = org->Upformortgage;
	copy->Mortgagedto = org->Mortgagedto;
}
void Cairo::SetCardParameters(int price, int fees) {
	this->CardPrice = price;
	this->feesTopay = fees;
}
void Cairo::SaveToFile(ofstream& output, int obj) {
	Card::SaveToFile(output, obj);
	output << " "<<this->CardPrice << " " << this->feesTopay << std::endl;
}