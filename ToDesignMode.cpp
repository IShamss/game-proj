#include "ToDesignMode.h"
#include "Grid.h"
#include "Player.h"
#include "NewGame.h"

ToDesignMode::ToDesignMode(ApplicationManager* pApp) : Action(pApp)
{
	decisiontoswitch = false;
}

ToDesignMode::~ToDesignMode()
{

}

void ToDesignMode::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	pOut->PrintMessage("Do you want to switch to design mode ending the game ? Enter 1 for yes or 0 for no ");
	int answer;
	answer = pIn->GetInteger(pOut);
	if (answer == 1)
	{
		decisiontoswitch = true;
	}
}

void ToDesignMode::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (decisiontoswitch == true)
	{
		Player* cp=NULL;
		pGrid->SetcurrPlayerNumber(0);
		int MaxSC = 1;
		int NumPlayersWithMax=0;
		int NumPlayersWithMaxSC = 0;
		int walletarr [4];
		int x, y;
		int ow;

		cp = pGrid->GetCurrentPlayer();

		for (int i = 0; i < 4; i=i+1)
		{
			cp = pGrid->GetCurrentPlayer();
			walletarr[i] = cp->GetWallet();
			pGrid->AdvanceCurrentPlayer();
		}
		cp = pGrid->GetCurrentPlayer();

		int maxwall = walletarr[0];

		for (int i = 0; i < 4; i = i + 1)
		{
			if (maxwall<walletarr[i])
			{
				maxwall = walletarr[i];
				ow = i;
			}
		}

		for (int i = 0; i < 4; i = i + 1)
		{
			if (maxwall == walletarr[i])
			{
				NumPlayersWithMax++;
			}
		}

		if (NumPlayersWithMax != 1)
		{
			int* StepCount= new int [(NumPlayersWithMax*2)];
			int counter=0;
			for (int i = 0; i < 4; i = i + 1)
			{
				if (cp->GetWallet()==maxwall)
				{
					StepCount[counter] = cp->GetStepCount();
					StepCount[counter + NumPlayersWithMax] = cp->GetPlayerNum();
					counter++;
				}
				pGrid->AdvanceCurrentPlayer();
				cp = pGrid->GetCurrentPlayer();
			}

			int so;

			for (int i = 0; i < NumPlayersWithMax; i = i + 1)
			{
				if (StepCount[i]>MaxSC)
				{
					MaxSC=StepCount[i];
					so = StepCount[i + NumPlayersWithMax];
				}
			}

			for (int i = 0; i < NumPlayersWithMax; i=i+1)
			{
				if (MaxSC == StepCount[i])
				{
					NumPlayersWithMaxSC++;
				}
			}

			if (NumPlayersWithMaxSC != 1)
			{
				string message1="";
				string message2="";
				for (int i = 0; i < 4; i++)
				{
					if (cp->GetWallet() == maxwall && cp->GetStepCount() == MaxSC)
					{
						message1 = message1 + "Player " + to_string(cp->GetPlayerNum())+" ";
					}
					pGrid->AdvanceCurrentPlayer();
					cp = pGrid->GetCurrentPlayer();
				}
				message2 = "are the winners with wallet value " + to_string(maxwall) + " and step count " + to_string(MaxSC);

				pOut->PrintMessage(message1+message2);
				pIn->GetPointClicked(x,y);
				pOut->ClearStatusBar();
			}
			else
			{
				pOut->PrintMessage("Player " + to_string(so) + " is the winner with wallet value " + to_string(maxwall)+" and step count "+to_string(MaxSC));
				pIn->GetPointClicked(x, y);
			}

			delete[] StepCount;

		}
		else
		{
			pOut->PrintMessage("Player "+to_string(ow)+" is the winner with wallet value "+to_string(maxwall));
			pIn->GetPointClicked(x, y);
		}

		NewGame N1(pManager);
		N1.Execute();
		pOut->CreateDesignModeToolBar();
	}
}