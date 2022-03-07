#include "AcceptMortgage.h"
#include "Grid.h"
#include "Card.h"
#include "Cairo.h"
#include "Luxor.h"
#include "Hurghada.h"
#include "Alexandria.h"
#include "Aswan.h"


Accept_Mortgage::Accept_Mortgage(ApplicationManager* pApp) :Action(pApp)
{

}

Accept_Mortgage::~Accept_Mortgage()
{

}

void Accept_Mortgage::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();   // Set pointers to Grid, Input and Output

	pOut->PrintMessage("Click on a cell containing the city you want to mortgage from another player");
	Cpos = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}

void Accept_Mortgage::Execute()
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
				Player* cp = pGrid->GetCurrentPlayer();
				if (Cnum == 7)
				{
					Cairo* pcairo = static_cast<Cairo*>(city);
					if (pcairo->Upformortgage == false)
					{
						pOut->PrintMessage("City isn't up for mortgage.Click to continue");
						int x, y;
						pIn->GetPointClicked(x, y);
						pOut->ClearStatusBar();
					}
					else
					{
						if (cp == pcairo->owner)
						{
							pOut->PrintMessage("Owner can't mortgage his own city.Click to continue");
							int x;
							int y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
						}
						else
						{
							if (cp->GetWallet() > pcairo->GetPrice() * 0.7)
							{
								pcairo->Mortgagedto = cp;
								cp->SetWallet(cp->GetWallet() - 0.7 * pcairo->GetPrice());
								Player* op = pcairo->owner;
								op->SetWallet(op->GetWallet() + 0.7 * pcairo->GetPrice());
								pcairo->Upformortgage = false;
								pOut->PrintMessage("City successfully mortgaged to current player.Click to continue");
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
								pGrid->ApplyforsameCairo(pcairo);
							}
							else
							{
								pOut->PrintMessage("Current player doesn't have enough coins in the wallet.Click to continue");
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
							}
						}
					}
				}
				else
				{
					if (Cnum == 8)
					{
						Alexandria* pcairo = static_cast<Alexandria*>(city);
						if (pcairo->Upformortgage == false)
						{
							pOut->PrintMessage("City isn't up for mortgage.Click to continue");
							int x, y;
							pIn->GetPointClicked(x, y);
							pOut->ClearStatusBar();
						}
						else
						{
							if (cp == pcairo->owner)
							{
								pOut->PrintMessage("Owner can't mortgage his own city.Click to continue");
								int x;
								int y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();
							}
							else
							{
								if (cp->GetWallet() > pcairo->GetPrice() * 0.7)
								{
									pcairo->Mortgagedto = cp;
									cp->SetWallet(cp->GetWallet() - 0.7 * pcairo->GetPrice());
									Player* op = pcairo->owner;
									op->SetWallet(op->GetWallet() + 0.7 * pcairo->GetPrice());
									pcairo->Upformortgage = false;
									pOut->PrintMessage("City successfully mortgaged to current player.Click to continue");
									int x, y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
									pGrid->ApplyforsameAlex(pcairo);
								}
								else
								{
									pOut->PrintMessage("Current player doesn't have enough coins in the wallet.Click to continue");
									int x, y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
								}
							}

						}
					}
					else
					{
						if (Cnum == 9)
						{
							Aswan* pcairo = static_cast<Aswan*>(city);
							if (pcairo->Upformortgage == false)
							{
								pOut->PrintMessage("City isn't up for mortgage.Click to continue");
								int x, y;
								pIn->GetPointClicked(x, y);
								pOut->ClearStatusBar();

							}
							else
							{
								if (cp == pcairo->owner)
								{
									pOut->PrintMessage("Owner can't mortgage his own city.Click to continue");
									int x;
									int y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();

								}
								else
								{
									if (cp->GetWallet() > pcairo->GetPrice() * 0.7)
									{
										pcairo->MortgagedTo = cp;
										cp->SetWallet(cp->GetWallet() - 0.7 * pcairo->GetPrice());
										Player* op = pcairo->owner;
										op->SetWallet(op->GetWallet() + 0.7 * pcairo->GetPrice());
										pcairo->Upformortgage = false;
										pOut->PrintMessage("City successfully mortgaged to current player.Click to continue");
										int x, y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();
										pGrid->ApplyforsameAswan(pcairo);
									}
									else
									{
										pOut->PrintMessage("Current player doesn't have enough coins in the wallet.Click to continue");
										int x, y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();
									}
								}

							}
						}
						else
						{
							if (Cnum == 10)
							{
								Luxor* pcairo = static_cast<Luxor*>(city);
								if (pcairo->Upformortgage == false)
								{
									pOut->PrintMessage("City isn't up for mortgage.Click to continue");
									int x, y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();

								}
								else
								{
									if (cp == pcairo->owner)
									{
										pOut->PrintMessage("Owner can't mortgage his own city.Click to continue");
										int x;
										int y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();
									}
									else
									{
										if (cp->GetWallet() > pcairo->GetPrice() * 0.7)
										{
											pcairo->Mortgagedto = cp;
											cp->SetWallet(cp->GetWallet() - 0.7 * pcairo->GetPrice());
											Player* op = pcairo->owner;
											op->SetWallet(op->GetWallet() + 0.7 * pcairo->GetPrice());
											pcairo->Upformortgage = false;
											pOut->PrintMessage("City successfully mortgaged to current player.Click to continue");
											int x, y;
											pIn->GetPointClicked(x, y);
											pOut->ClearStatusBar();
											pGrid->ApplyforsameLuxor(pcairo);

										}
										else
										{
											pOut->PrintMessage("Current player doesn't have enough coins in the wallet.Click to continue");
											int x, y;
											pIn->GetPointClicked(x, y);
											pOut->ClearStatusBar();

										}
									}

								}
							}
							else
							{
								Hurghada* pcairo = static_cast<Hurghada*>(city);
								if (pcairo->Upformortgage == false)
								{
									pOut->PrintMessage("City isn't up for mortgage.Click to continue");
									int x, y;
									pIn->GetPointClicked(x, y);
									pOut->ClearStatusBar();
								}
								else
								{
									if (cp == pcairo->owner)
									{
										pOut->PrintMessage("Owner can't mortgage his own city.Click to continue");
										int x;
										int y;
										pIn->GetPointClicked(x, y);
										pOut->ClearStatusBar();
									}
									else
									{
										if (cp->GetWallet() > pcairo->GetPrice() * 0.7)
										{
											pcairo->Mortgagedto = cp;
											cp->SetWallet(cp->GetWallet() - 0.7 * pcairo->GetPrice());
											Player* op = pcairo->owner;
											op->SetWallet(op->GetWallet() + 0.7 * pcairo->GetPrice());
											pcairo->Upformortgage = false;
											pOut->PrintMessage("City successfully mortgaged to current player.Click to continue");
											int x, y;
											pIn->GetPointClicked(x, y);
											pOut->ClearStatusBar();
											pGrid->ApplyforsameHurg(pcairo);
										}
										else
										{
											pOut->PrintMessage("Current player doesn't have enough coins in the wallet.Click to continue");
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
		}
	}
}