#include"ReturnMortgage.h"
#include"Grid.h"
#include"Card.h"
#include"Cairo.h"
#include "Alexandria.h"
#include "Hurghada.h"
#include "Luxor.h"
#include "Aswan.h"

Return_Mortgage::Return_Mortgage(ApplicationManager* pApp) :Action(pApp)
{

}

Return_Mortgage::~Return_Mortgage()
{

}

void Return_Mortgage::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	pOut->PrintMessage("Click on a cell containing the city you want to pay its mortgage");
	Cpos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void Return_Mortgage::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	ReadActionParameters();

	if (Cpos.HCell() != -1)
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
				Player* cp = pGrid->GetCurrentPlayer();
				if (Cnum == 7)
				{
					Cairo* pCairo = static_cast<Cairo*>(city);
					if (cp == pCairo->owner && cp->GetWallet() > pCairo->GetPrice() * 0.7 && pCairo->Mortgagedto != NULL)
					{
						Player* mto = pCairo->Mortgagedto;
						mto->SetWallet(mto->GetWallet() + 0.7 * pCairo->GetPrice());
						cp->SetWallet(cp->GetWallet() - 0.7 * pCairo->GetPrice());
						pCairo->Mortgagedto = NULL;
						pOut->PrintMessage("City's mortgage sucessfully returned. Click to continue");
						int x;
						int y;
						pIn->GetPointClicked(x, y);
						pOut->ClearStatusBar();
						pGrid->ApplyforsameCairo(pCairo);

					}
					else
					{
						pOut->PrintMessage("Current Player isn't original owner of city or doesn't have enough coins to return mortgage . Click to continue");
						int x;
						int y;
						pIn->GetPointClicked(x, y);
						pOut->ClearStatusBar();
					}
				}
				else
				{
					if (Cnum == 8)
					{
						Alexandria* pCairo = static_cast<Alexandria*>(city);
						if (cp == pCairo->owner && cp->GetWallet() > pCairo->GetPrice() * 0.7 && pCairo->Mortgagedto != NULL)
						{
							Player* mto = pCairo->Mortgagedto;
							mto->SetWallet(mto->GetWallet() + 0.7 * pCairo->GetPrice());
							cp->SetWallet(cp->GetWallet() - 0.7 * pCairo->GetPrice());
							pCairo->Mortgagedto = NULL;
							pOut->PrintMessage("City's mortgage sucessfully returned. Click to continue");
							int x;
							int y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
							pGrid->ApplyforsameAlex(pCairo);

						}
						else
						{
							pOut->PrintMessage("Current Player isn't original owner of city or doesn't have enough coins to return mortgage . Click to continue");
							int x;
							int y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();

						}
					}
					else
					{
						if (Cnum == 9)
						{
							Aswan* pCairo = static_cast<Aswan*>(city);
							if (cp == pCairo->owner && cp->GetWallet() > pCairo->GetPrice() * 0.7 && pCairo->MortgagedTo != NULL)
							{
								Player* mto = pCairo->MortgagedTo;
								mto->SetWallet(mto->GetWallet() + 0.7 * pCairo->GetPrice());
								cp->SetWallet(cp->GetWallet() - 0.7 * pCairo->GetPrice());
								pCairo->MortgagedTo = NULL;
								pOut->PrintMessage("City's mortgage sucessfully returned. Click to continue");
								int x;
								int y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
								pGrid->ApplyforsameAswan(pCairo);

							}
							else
							{
								pOut->PrintMessage("Current Player isn't original owner of city or doesn't have enough coins to return mortgage . Click to continue");
								int x;
								int y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();

							}
						}
						else
						{
							if (Cnum == 10)
							{
								Luxor* pCairo = static_cast<Luxor*>(city);
								if (cp == pCairo->owner && cp->GetWallet() > pCairo->GetPrice() * 0.7 && pCairo->Mortgagedto != NULL)
								{
									Player* mto = pCairo->Mortgagedto;
									mto->SetWallet(mto->GetWallet() + 0.7 * pCairo->GetPrice());
									cp->SetWallet(cp->GetWallet() - 0.7 * pCairo->GetPrice());
									pCairo->Mortgagedto = NULL;
									pOut->PrintMessage("City's mortgage sucessfully returned. Click to continue");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
									pGrid->ApplyforsameLuxor(pCairo);

								}
								else
								{
									pOut->PrintMessage("Current Player isn't original owner of city or doesn't have enough coins to return mortgage . Click to continue");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();

								}
							}
							else
							{
								Hurghada* pCairo = static_cast<Hurghada*>(city);
								if (cp == pCairo->owner && cp->GetWallet() > pCairo->GetPrice() * 0.7 && pCairo->Mortgagedto != NULL)
								{
									Player* mto = pCairo->Mortgagedto;
									mto->SetWallet(mto->GetWallet() + 0.7 * pCairo->GetPrice());
									cp->SetWallet(cp->GetWallet() - 0.7 * pCairo->GetPrice());
									pCairo->Mortgagedto = NULL;
									pOut->PrintMessage("City's mortgage sucessfully returned. Click to continue");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
									pGrid->ApplyforsameHurg(pCairo);

								}
								else
								{
									pOut->PrintMessage("Current Player isn't original owner of city or doesn't have enough coins to return mortgage . Click to continue");
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
	else
	{
		pOut->PrintMessage("No Cell was selected. Action terminated. Click to continue");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
}



