#include "SellCity.h"
#include "Grid.h"
#include "Card.h"
#include "Cairo.h"
#include "Luxor.h"
#include "Hurghada.h"
#include "Alexandria.h"
#include "Aswan.h"

SellCity::SellCity(ApplicationManager* pApp) :Action(pApp)
{

}

SellCity::~SellCity()
{

}

void SellCity::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	pOut->PrintMessage("Click on a cell containing the city you want to sell");
	Cpos=pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void SellCity::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	Cell* pcard = pGrid->GetCell(Cpos);
    Card* card=pcard->HasCard();

	if (Cpos.HCell() == -1)
	{
		pOut->PrintMessage("Invalid cell selected. Action terminated. Click to continue");
		int x, y;
		pIn->GetPointClicked(x, y);
		return;
	}

	if (card == NULL)
	{
		pOut->PrintMessage("You have chosen a cell with no city. Click to continue");
		int x;
		int y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	else
	{
		int Cnum=card->GetCardNumber();

		if (Cnum < 7 || Cnum > 11)
		{
			pOut->PrintMessage("You have chosen a cell with no city card. Click to continue");
			int x;
			int y;
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
		}
		else
		{
			Player* pp = pGrid->GetCurrentPlayer();
			
			if (Cnum == 7)
			{
				Cairo* pCairo = static_cast<Cairo*>(card);
				Player* po = pCairo->owner;
				if (po == pp)
				{
					pp->SetWallet(pp->GetWallet() + (pCairo->GetPrice() * 0.9));
					pCairo->owner = NULL;
					pCairo->Setbought(false);
					pOut->PrintMessage("City Sold. Click to continue");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
					pGrid->ApplyforsameCairo(pCairo);
				}
				else
				{
					pOut->PrintMessage("Current player isn't the owner of the City");
					int x, y;
					pIn->GetPointClicked(x, y);
					pOut->ClearStatusBar();
				}
			}
			else
			{
				if (Cnum == 8)
				{
					Alexandria* pAlex = static_cast<Alexandria*>(card);
					Player* po = pAlex->owner;
					if (po == pp)
					{
						pp->SetWallet(pp->GetWallet() + (pAlex->GetPrice() * 0.9));
						pAlex->owner = NULL;
						pOut->PrintMessage("City Sold. Click to continue");
						pAlex->Setbought(false);
						int x, y;
						pIn->GetPointClicked(x, y);
						pOut->ClearStatusBar();
						pGrid->ApplyforsameAlex(pAlex);
					}
					else
					{
						pOut->PrintMessage("Current player isn't the owner of the City");
						int x, y;
						pIn->GetPointClicked(x, y);
						pOut->ClearStatusBar();
					}
				}
				else
				{
					if (Cnum == 9)
					{
						Aswan* pAswan = static_cast<Aswan*>(card);
						Player* po = pAswan->owner;
						if (po == pp)
						{
							pp->SetWallet(pp->GetWallet() + (pAswan->GetPrice() * 0.9));
							pAswan->owner = NULL;
							pAswan->Setbought(false);
							pOut->PrintMessage("City Sold. Click to continue");
							int x, y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
							pGrid->ApplyforsameAswan(pAswan);
						}
						else
						{
							pOut->PrintMessage("Current player isn't the owner of the City");
							int x, y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
						}
					}
					else
					{
						if (Cnum == 10)
						{
							Luxor* pLuxor = static_cast<Luxor*>(card);
							Player *po = pLuxor->owner;
							if (po == pp)
							{
								pp->SetWallet(pp->GetWallet() + (pLuxor->GetPrice() * 0.9));
								pLuxor->owner = NULL;
								pLuxor->Setbought(false);
								pOut->PrintMessage("City Sold. Click to continue");
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
								pGrid->ApplyforsameLuxor(pLuxor);
							}
							else
							{
								pOut->PrintMessage("Current player isn't the owner of the City");
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
							}
						}
						else
						{
							Hurghada* pHurg = static_cast<Hurghada*>(card);
							Player* po = pHurg->owner;
							if (po == pp)
							{
								pp->SetWallet(pp->GetWallet() + (pHurg->GetPrice() * 0.9));
								pHurg->owner = NULL;
								pOut->PrintMessage("City Sold. Click to continue");
								pHurg->Setbought(false);
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
								pGrid->ApplyforsameHurg(pHurg);
							}
							else
							{
								pOut->PrintMessage("Current player isn't the owner of the City");
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
							}
						}

					}

				}
			}
		}

	}
}