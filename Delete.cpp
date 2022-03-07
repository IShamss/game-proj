#include "Delete.h"

#include "Input.h"
#include "Output.h"
#include "Cell.h"
#include "Action.h"
#include "Grid.h"
#include "PLayer.h"

Delete::Delete(ApplicationManager* pApp) : 
	Action(pApp)
{
}
void Delete::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	pOut->PrintMessage("To delete ladder choose cell containing start of ladder.Click to continue...");
	pIn->GetPointClicked(x, y);
	pOut->PrintMessage("To delete snake choose cell containing head of snake.Click to continue... ");
	pIn->GetPointClicked(x, y);
	pOut->PrintMessage("Click on Cell containing object you want to delete ...");
	Cpos=pIn->GetCellClicked();
	pOut->ClearStatusBar();
}
void Delete::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut=pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (Cpos.HCell() == -1)
	{
		pOut->PrintMessage("Invalid cell selected. Click to continue ...");
		Cpos = pIn->GetCellClicked();
		pOut->ClearStatusBar();
	}
	 else
	 {
		Cell* pcell = pGrid->GetCell(Cpos);
		pGrid->RemoveObjectFromCell(Cpos);
		pOut->PrintMessage("Object deleted. Click to continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	   }
}