#include "LoadGridAction.h"
#include "Grid.h"
#include <fstream>
#include "CellPosition.h"
#include"Alexandria.h"
#include"Aswan.h"
#include"BackwardCard_3.h"
#include"BenefitAllCard.h"
#include"Cairo.h"
#include"Card.h"
#include"DecWalletCard_1.h"
#include"FireCard_5.h"
#include"FreezeCard.h"
#include"Hurghada.h"
#include"LoseCityCard.h"
#include"Luxor.h"
#include"NextCard_2.h"
#include"PreventCard_4.h"
#include"ReturnMortgage.h"
#include"TakeCityCard.h"
#include"Ladder.h"
#include"Snake.h"
#include"ReturnMortgagedCard.h"
#include "CoinSet.h"

LoadGridAction::LoadGridAction(ApplicationManager* pApp) :Action(pApp) {

}

LoadGridAction::~LoadGridAction() {

}

void LoadGridAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("enter the name of the file : ");
	this->fname = pIn->GetString(pOut);
	pOut->ClearStatusBar();
}

void LoadGridAction::Execute() {
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pGrid->RemoveAllObjects();

	ifstream inputFile(this->fname + ".txt");
	int num;
	inputFile >> num;
	pGrid->LoadGameObjects(num, 'l', inputFile, pGrid);


	inputFile >> num; //this num represents the total snakes
	pGrid->LoadGameObjects(num, 's', inputFile, pGrid);

	inputFile >> num; //the total number of cards
	pGrid->LoadGameObjects(num, 'c', inputFile, pGrid);
	inputFile >> num; //the coinset number
	pGrid->LoadGameObjects(num, 'y', inputFile, pGrid);
}