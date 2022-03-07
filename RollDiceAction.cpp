#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	bool Game;
	Game = pGrid->GetEndGame();

	if (Game == true)
	{
		pOut->PrintMessage("Game has ended if you want to start a newgame press on New icon in tool bar above");
		int x;
		int y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	else
	{
		// -- If not ended, do the following --:

		// 2- Generate a random number from 1 to 6 --> This step is done for you
		srand((int)time(NULL)); // time is for different seed each run
		int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

		// 3- Get the "current" player from pGrid

		Player* pp;
		pp = pGrid->GetCurrentPlayer();


		// 4- Move the currentPlayer using function Move of class player

		pp->Move(pGrid,diceNumber);

		// Case where user wanted to perform further actions like mortgage actions as the project document described a case where the player use a mortgage icon after rolling his dice

		bool furtheraction = true;

		ActionType* Act=NULL;

		while (furtheraction == true)
		{
			pOut->PrintMessage("Your turn is about to end. Click on An Action icon if you want to perform it, anywhere else to continue.");

			Act = new ActionType(pManager->GetUserAction());

			if (*Act==STATUS || *Act==EMPTY || *Act==GRID_AREA)
			{
				furtheraction = false;
				pOut->ClearStatusBar();
			}
			else
			{
				if (*Act == ROLL_DICE || *Act == Input_Dice_Value)
				{
					pOut->PrintMessage("You can't choose roll dice or input dice as you have already rolled this turn. Click to continue");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
				else
				{
					if (*Act == TO_DESIGN_MODE || *Act == New_Game)
					{
						pManager->ExecuteAction(*Act);
						furtheraction = false;
					}
					else
					{
						pManager->ExecuteAction(*Act);
					}
				}
			}
		}

		if (*Act != New_Game)
		pGrid->AdvanceCurrentPlayer();

		if (Act != NULL)
			delete Act;

		// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
	}
}

RollDiceAction::~RollDiceAction()
{
}
