#include "CutAction.h"
#include "CellPosition.h"
#include "Grid.h"
#include "Card.h"
#include "Input.h"
#include "Output.h"
#include "CoinSet.h"

CutAction::CutAction(ApplicationManager *pApp) : Action(pApp) {
	//initialize the cut action
}

CutAction::~CutAction() {

}

void CutAction::ReadActionParameters() {
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//we need the source cell which the user clicked on
	pOut->PrintMessage("Enter cell containing card or coinset you want to cut ...");

	source = pIn->GetCellClicked();
}

void CutAction::Execute() {

	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;


	if (source.HCell() == -1)
	{
		pOut->PrintMessage("Invalid cell. Action terminated");
	}
	else
	{
		Cell* cello = pGrid->GetCell(source);
		Card* card = NULL;
		card = cello->HasCard();
		CoinSet* coinset = NULL;
		coinset = cello->HasCoinSet();

		if (coinset != NULL)
		{
			pGrid->SetCoinClipboard(coinset);
			pGrid->PrintErrorMessage("Coinset is cut. Click to continue ...");
			pGrid->Setfromcopy(false);
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
		}
		else if (card != NULL) {
			pGrid->SetClipboard(card);
			pGrid->PrintErrorMessage("Card is cut. Click to continue ...");
			pGrid->Setfromcopy(false);
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
		}
		else {
			pGrid->PrintErrorMessage("No card or coinset object in cell. Click to continue ...");
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
		}
	}
}