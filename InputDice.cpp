#include "InputDice.h"
#include "Grid.h"
#include "Player.h"

InputDice::InputDice(ApplicationManager* pApp) : Action(pApp)
{
	dicenumber = 0;
}

InputDice::~InputDice()
{

}

void InputDice::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter Dice value from 1-6: ");
	int dice = pIn->GetInteger(pOut);

	int x;
	int y;

	while (dice > 6 || dice < 1)
	{
		pOut->PrintMessage("Invalid Dice value entered. Click to continue ....");
		pIn->GetPointClicked(x, y);
		pOut->PrintMessage("Enter Dice valur from 1-6: ");
	    dice = pIn->GetInteger(pOut);
	}

	pOut->ClearStatusBar();

	dicenumber = dice;
}

void InputDice::Execute()
{
	ReadActionParameters();

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

		Player* cp;

		cp = pGrid->GetCurrentPlayer();

		cp->Move(pGrid, dicenumber);

		// Case where user wanted to perform further actions like mortgage actions as the project document described a case where the player use a mortgage icon after rolling his dice

		bool furtheraction = true;

		ActionType* Act = NULL;

		while (furtheraction == true)
		{
			pOut->PrintMessage("Your turn is about to end. Click on An Action icon if you want to perform it, anywhere else to continue.");

			Act = new ActionType(pManager->GetUserAction());

			if (*Act == STATUS || *Act == EMPTY || *Act == GRID_AREA)
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