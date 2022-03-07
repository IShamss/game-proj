#include "AddCardAction.h"

#include "Input.h"
#include "Output.h"
#include "DecWalletCard_1.h"
#include "FireCard_5.h"
#include "BackwardCard_3.h"
#include "PreventCard_4.h"
#include "NextCard_2.h"
#include "FreezeCard.h"
#include "Cairo.h"
#include "Alexandria.h"
#include "Aswan.h"
#include "Hurghada.h"
#include "Luxor.h"
#include "TakeCityCard.h"
#include "LoseCityCard.h"
#include "ReturnMortgagedCard.h"
#include "BenefitAllCard.h"

AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Enter the card number");
	this->cardNumber = pIn->GetInteger(pOut);
	if (this->cardNumber < 1 || this->cardNumber>14) {
		pOut->PrintMessage("Enter a valid number whithin the range 1-14");
	}
	//first we will dereference the grid pointer to get the getClipboard which returns a card pointer 
	//which can be dereferenced to get it's number

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Click on cell you want to the card to");
	CellPosition newCell = pIn->GetCellClicked();
	if (newCell.IsValidCell()) {
		this->cardPosition = newCell;
	}
	else {
		pOut->PrintMessage("Enter a valid cell");
	}

	// 4- Make the needed validations on the read parameters


	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type
	switch (cardNumber)
	{
	case 1:
		pCard = new DecWalletCard_1(cardPosition);
		break;
	case 2:
		pCard = new NextCard_2(cardPosition);
		break;
	case 3:
		pCard = new BackwardCard_3(cardPosition);
		break;
	case 4:
		pCard = new PreventCard_4(cardPosition);
		break;
	case 5:
		pCard = new FireCard_5(cardPosition);
		break;
	case 6:
		pCard = new FreezeCard(cardPosition);
		break;
	case 7:
		pCard = new Cairo(cardPosition);
		break;
	case 8:
		pCard = new Alexandria(cardPosition);
		break;
	case 9:
		pCard = new Aswan(cardPosition);
		break;
	case 10:
		pCard = new Luxor(cardPosition);
		break;
	case 11:
		pCard = new Hurghada(cardPosition);
		break;
	case 12:
		pCard = new TakeCityCard(cardPosition);
		break;
	case 13:
		pCard = new LoseCityCard(cardPosition);
		break;
	case 14:
		pCard = new ReturnMortgagedCard(cardPosition);
		break;
	case 15:
		pCard = new BenefitAllCard(cardPosition);
		break;

		// A- Add the remaining cases
		//will be implemented after the cards
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{
		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* gridPtr = pManager->GetGrid();

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type

		pCard->ReadCardParameters(gridPtr);
		// C- Add the card object to the GameObject of its Cell:

		bool val = gridPtr->AddObjectToCell(pCard);
		if (!val) {
			pManager->GetGrid()->PrintErrorMessage("There is an object in this cell");
		}
		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar

	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}


//Mohamed Shams