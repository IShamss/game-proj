#include "NewGame.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"

NewGame::NewGame(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

NewGame::~NewGame()
{
   // Destructor
}

void NewGame::ReadActionParameters()
{
}

void NewGame::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output
	Player* pp= NULL;   // Creating a player pointer 
	CellPosition C(8, 0);  // Creating Cell position of first cell in grid
	pOut->PrintMessage("Setting New Game"); // Indication that this action has started
	pGrid->SetcurrPlayerNumber(0);  // Set current player of grid to player 0
	pGrid->Resetcity();   // Reset cities datamembers to default 
	pGrid->SetEndGame(false);
	for (int i = 0; i < MaxPlayerCount; i++)   // Iteration for each of 4 players
	{
		pp = pGrid->GetCurrentPlayer();    // Getting current player
		pp->SetWallet(100);          // Setting wallet to 100
		pp->SetTurnCount(0);         // Set turncount to 0
		pp->SetStepCount(1);
		pGrid->UpdatePlayerCell(pp, C);  // Update player's cell datamember to have cellposition of first cell and draws player in first cell
		pGrid->AdvanceCurrentPlayer();  // Advance curr player to next to apply the above steps to following player
	}
	pOut->ClearStatusBar();
}
