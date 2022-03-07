#include "OfferMortgage.h"
#include "Grid.h"
#include "Card.h"
#include "Cairo.h"
#include "Luxor.h"
#include "Hurghada.h"
#include "Alexandria.h"
#include "Aswan.h"


Offer_Mortgage::Offer_Mortgage(ApplicationManager* pApp) :Action(pApp)
{

}

Offer_Mortgage::~Offer_Mortgage()
{

}

void Offer_Mortgage::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	pOut->PrintMessage("Click on a cell containing the city you want to mortgage to another player");
	Cpos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void Offer_Mortgage::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	ReadActionParameters();

	if (Cpos.HCell() == -1)      // in case user doesn't select a grid cell
	{
		pOut->PrintMessage("No Cell was clicked. Action terminated. Click to continue");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	else
	{
		Cell* pCity = pGrid->GetCell(Cpos);
		Card* city = pCity->HasCard();
		if (city == NULL)
		{
			pOut->PrintMessage("You have chosen a cell with no city. Click to continue");
			int x;
			int y;
			pIn->GetPointClicked(x, y);
			pOut->ClearStatusBar();
		}
		else
		{
			int Cnum = city->GetCardNumber();

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
					Cairo* pcairo = static_cast<Cairo*>(city);
					Player* po = pcairo->owner;            //getting owner player
					if (pp != po)     // checking current player owns the city
					{
						pOut->PrintMessage("Current Player isn't the owner of the city. Click to continue ");
						int x;
						int y;
						pIn->GetPointClicked(x, y);
						pOut->ClearStatusBar();
					}
					else
					{
						if (pcairo->Mortgagedto == pcairo->owner)
						{
							pcairo->Upformortgage = true;              // making city up for mortgage for other players
							pOut->PrintMessage("City up for mortgage for other players. Click to continue");
							int x;
							int y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
							pGrid->ApplyforsameCairo(pcairo);

						}
						else
						{
							pOut->PrintMessage("Owner trying to offer a city he has already mortgaged. Action terminated");
							int x;
							int y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
						}
					}
				}
				else
				{
					if (Cnum == 8)
					{
						Alexandria* pcairo = static_cast<Alexandria*>(city);
						Player* po = pcairo->owner;            //getting owner player
						if (pp != po)     // checking current player owns the city
						{
							pOut->PrintMessage("Current Player isn't the owner of the city. Click to continue ");
							int x;
							int y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();

						}
						else
						{
							if (pcairo->Mortgagedto == po)
							{
								pcairo->Upformortgage = true;              // making city up for mortgage for other players
								pOut->PrintMessage("City up for mortgage for other players. Click to continue");
								int x;
								int y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
								pGrid->ApplyforsameAlex(pcairo);

							}
							else
							{
								pOut->PrintMessage("Owner trying to offer a city he has already mortgaged. Action terminated");
								int x;
								int y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
							}
						}
					}
					else
					{
						if (Cnum == 9)
						{
							Aswan* pcairo = static_cast<Aswan*>(city);
							Player* po = pcairo->owner;            //getting owner player
							if (pp != po)     // checking current player owns the city
							{
								pOut->PrintMessage("Current Player isn't the owner of the city. Click to continue ");
								int x;
								int y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
							}
							else
							{
								if (pcairo->MortgagedTo == po)
								{
									pcairo->Upformortgage = true;              // making city up for mortgage for other players
									pOut->PrintMessage("City up for mortgage for other players. Click to continue");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
									pGrid->ApplyforsameAswan(pcairo);
								}
								else
								{
									pOut->PrintMessage("Owner trying to offer a city he has already mortgaged. Action terminated");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
								}
							}
						}
						else
						{
							if (Cnum == 10)
							{
								Luxor* pcairo = static_cast<Luxor*>(city);
								Player* po = pcairo->owner;            //getting owner player
								if (pp != po)     // checking current player owns the city
								{
									pOut->PrintMessage("Current Player isn't the owner of the city. Click to continue ");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();

								}
								else
								{
									if (pcairo->Mortgagedto == po)
									{
										pcairo->Upformortgage = true;              // making city up for mortgage for other players
										pOut->PrintMessage("City up for mortgage for other players. Click to continue");
										int x;
										int y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();
										pGrid->ApplyforsameLuxor(pcairo);

									}
									else
									{
										pOut->PrintMessage("Owner trying to offer a city he has already mortgaged. Action terminated");
										int x;
										int y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();

									}
								}
							}
							else
							{
								Hurghada* pcairo = static_cast<Hurghada*>(city);
								Player* po = pcairo->owner;            //getting owner player
								if (pp != po)     // checking current player owns the city
								{
									pOut->PrintMessage("Current Player isn't the owner of the city. Click to continue ");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();

								}
								else
								{
									if (pcairo->Mortgagedto == po)
									{
										pcairo->Upformortgage = true;              // making city up for mortgage for other players
										pOut->PrintMessage("City up for mortgage for other players. Click to continue");
										int x;
										int y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();
										pGrid->ApplyforsameHurg(pcairo);

									}
									else
									{
										pOut->PrintMessage("Owner trying to offer a city he has already mortgaged. Action terminated");
										int x;
										int y;
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
	}
}