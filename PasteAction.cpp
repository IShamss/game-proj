#include "PasteAction.h"
#include "CellPosition.h"
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
#include "CoinSet.h"

class FireCard_5;
class FreezeCard_6;
class Cairo;
class Alexandria;
class Luxor;
class Aswan;
class Hurghada;
class TakeCityCard_12;
class LoseCityCard_13;
class ReturnMortgagedCard_14;
class BenifitAllCard_15;

PasteAction::PasteAction(ApplicationManager* pApp) :Action(pApp) {

}
PasteAction::~PasteAction() {

}
void PasteAction::ReadActionParameters() {
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//then get the cell to paste to it
	pOut->PrintMessage("Enter cell to paste object in ... ");
	destination = pIn->GetCellClicked();
}

void PasteAction::Execute() 
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	if (destination.HCell() == -1)
	{
		pOut->PrintMessage("invalid cell. Action terminated. click to continue");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	else
	{
		Card* clipCard = pGrid->GetClipboard();
		CoinSet* clipCoin = pGrid->GetCoinClipboard();
		
		int choice;
		pOut->PrintMessage("Enter 1 to paste coinset object, Enter 2 to paste Card object");
		choice=pIn->GetInteger(pOut);
		if (choice == 1)
		{
			if (pGrid->Getfromcopy() == true)
			{
				if (clipCoin == NULL)
				{
					pOut->PrintMessage("No coinset in clipboard. Action terminated. click to continue");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
				else
				{
					int amount = clipCoin->getAmount();
					CoinSet* paste = new CoinSet(amount, destination);
					pGrid->AddObjectToCell(paste);
					pOut->PrintMessage("CoinSet pasted in desired cell. click to continue ...");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
			}
			else
			{
				if (clipCoin == NULL)
				{
					pOut->PrintMessage("No coinset in clipboard. Action terminated. click to continue");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
				else
				{
					CellPosition Cpos=clipCoin->GetPosition();
					pGrid->Removeobjectfromcellnodelete(Cpos);
					clipCoin->SetPosition(destination);
					pGrid->AddObjectToCell(clipCoin);
					pOut->PrintMessage("CoinSet pasted in desired cell. click to continue ...");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
			}
		}
		else if (choice == 2)
			{
			if (pGrid->Getfromcopy() == true)
			{
				if (clipCard == NULL)
				{
					pOut->PrintMessage("No card in clipboard. Action terminated. click to continue");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
				else
				{
					int cardNumber = clipCard->GetCardNumber();
					Card* pCard = NULL; // will point to the card object type
					switch (cardNumber)
					{
					case 1:
						pCard = new DecWalletCard_1(destination);
						break;
					case 2:
						pCard = new NextCard_2(destination);
						break;
					case 3:
						pCard = new BackwardCard_3(destination);
						break;
					case 4:
						pCard = new PreventCard_4(destination);
						break;
					case 5:
						pCard = new FireCard_5(destination);
						break;
					case 6:
						pCard = new FreezeCard(destination);
						break;
					case 7:
						pCard = new Cairo(destination);
						break;
					case 8:
						pCard = new Alexandria(destination);
						break;
					case 9:
						pCard = new Aswan(destination);
						break;
					case 10:
						pCard = new Luxor(destination);
						break;
					case 11:
						pCard = new Hurghada(destination);
						break;
					case 12:
						pCard = new TakeCityCard(destination);
						break;
					case 13:
						pCard = new LoseCityCard(destination);
						break;
					case 14:
						pCard = new ReturnMortgagedCard(destination);
						break;
					case 15:
						pCard = new BenefitAllCard(destination);
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
				}
			}
			else
			{
				CellPosition opos = clipCard->GetPosition();
				pGrid->Removeobjectfromcellnodelete(opos);
				clipCard->SetPosition(destination);
				pGrid->AddObjectToCell(clipCard);
				pOut->PrintMessage("Card pasted in desired cell. click to continue ...");
				int x, y;
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
			}
			}
		else
			{
				pOut->PrintMessage("Invalid choice. Action terminated. click to continue");
				int x, y;
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
			}
		
	}
}