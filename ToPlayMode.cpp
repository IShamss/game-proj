#include "ToPlayMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "NewGame.h"
#include "SaveGridAction.h"

ToPlayMode::ToPlayMode(ApplicationManager* pApp) : Action(pApp)
{

}

ToPlayMode::~ToPlayMode()
{
	// Destructor
}

void ToPlayMode::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	pOut->PrintMessage("Do you want to save the grid before switching to design mode ending the game ? Enter 1 for yes or 0 for no ");
	int answer;
	answer = pIn->GetInteger(pOut);
	if (answer == 1)
	{
		decisiontosave = true;
	}
}

void ToPlayMode::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	if (decisiontosave == true)
	{
		SaveGridAction Save(pManager);
		Save.Execute();
	}

	NewGame NG(pManager);
	NG.Execute();

	pOut->CreatePlayModeToolBar();
	
}