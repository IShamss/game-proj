#include "Card.h"
#include<fstream>
#include<iostream>
#include"AcceptMortgage.h"
#include"Alexandria.h"
#include"Aswan.h"
#include"BackwardCard_3.h"
#include"BenefitAllCard.h"
#include"Cairo.h"
#include"DecWalletCard_1.h"
#include"FireCard_5.h"
#include"FreezeCard.h"
#include"Hurghada.h"
#include"Luxor.h"
#include"NextCard_2.h"
#include"PreventCard_4.h"
#include"ReturnMortgagedCard.h"
#include"TakeCityCard.h"
#include"LoseCityCard.h"
#include"Grid.h"


Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	cardNumber = cnum; // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);


}
void Card::Get_CardPtr(int num, ifstream&inputFile, Grid*newGrid) {
	int i = 0;
	while (i < num) {
		int cellNum, cardNum,cardPrice,feesAmount;
		inputFile >> cellNum >> cardNum >> cardPrice >> feesAmount;
		CellPosition temp = CellPosition(cellNum);
		Card* newCard;
		if (cardNum == 1) {
			newCard = new DecWalletCard_1(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 2) {
			newCard = new NextCard_2(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 3) {
			newCard = new BackwardCard_3(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 4) {
			newCard = new PreventCard_4(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 5) {
			newCard = new FireCard_5(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 6) {
			newCard = new FreezeCard(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 7) {
			newCard = new Cairo(temp);
			newCard.SetCardParameters(cardPrice, feesAmount);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 8) {
			newCard = new Alexandria(temp);
			newCard.SetCardParameters(cardPrice, feesAmount);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 9) {
			newCard = new Aswan(temp);
			newCard.SetCardParameters(cardPrice, feesAmount);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 10) {
			newCard = new Luxor(temp);
			newCard.SetCardParameters(cardPrice, feesAmount);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 11) {
			newCard = new Hurghada(temp);
			newCard.SetCardParameters(cardPrice, feesAmount);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 12) {
			newCard = new TakeCityCard(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 13) {
			newCard = new LoseCityCard(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 14) {
			newCard = new ReturnMortgagedCard(temp);
			newGrid->AddObjectToCell(newCard);
		}
		else if (cardNum == 15) {
			newCard = new BenefitAllCard(temp);
			newGrid->AddObjectToCell(newCard);
		}

		i++;
	}
}
	

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{

	// The following line is to print the following message if a player reaches a card of any type

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

Card::~Card()
{
}

void Card::SetPosition(CellPosition cpos)
{
	position = cpos;
}



void Card::SaveToFile(ofstream& output, int obj) {
	if (obj == 3) {
		GameObject::SaveToFile(output, obj);
		int cardNum = this->cardNumber;
		
		output << " " << cardNum ;
		
	}
}


