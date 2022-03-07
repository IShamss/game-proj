#include "AddCoinSet.h"

#include "Input.h"
#include "Output.h"


AddCoinSetAction::AddCoinSetAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCoinSetAction::~AddCoinSetAction()
{

}

void AddCoinSetAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//get the cell that the user selected and set it as temporary
	pOut->PrintMessage("Click on cell to add coinset ...");
	CellPosition temp = pIn->GetCellClicked();
	if (temp.IsValidCell()) {
		this->cell = temp;
	}
	//get the amount of the coinset from the user input
	pOut->PrintMessage("Enter amount of coins in coin set");
	this->amount = pIn->GetInteger(pOut);

	//then clear the status bar
	pOut->ClearStatusBar();

}

void AddCoinSetAction::Execute() {
	//read the parameters of the action
	ReadActionParameters();
	//creating a new pointer to the coinset object

	Grid* pGrid = pManager->GetGrid(); //we want the grid to add the object to it
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	if (cell.HCell() == -1)
	{
		return;
		pOut->PrintMessage("Action terminated");
	}
	else
	{
		CoinSet* cset = new CoinSet(amount,cell);

		bool added = pGrid->AddObjectToCell(cset);

		if (!added) {
			//if we failed to add the object then output an error message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
	}
}


// Mohamed Shams