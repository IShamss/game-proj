#include "SaveGridAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include <fstream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) :Action(pApp) {

}
SaveGridAction::~SaveGridAction() {

}
void SaveGridAction::ReadActionParameters() {
	//get a pointer to the grid, input and output
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//get the name of the file from the user
	pOut->PrintMessage("Enter the name of the file to save");
	this->fname = pIn->GetString(pOut);

	//then clear the status bar

	pOut->ClearStatusBar();
}

void SaveGridAction::Execute() {
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	this->fname += ".txt";
	int ladderNum = pGrid->ladderCount(); //total number of ladders
	int snakeNum = pGrid->snakeCount();//total numebr of snakes

	int cardNum = pGrid->cardCount(); //total number of cards
	int coinNum = pGrid->coinCount();
	//this is the stream for reading and writing to files
	std::ofstream outputFile(this->fname, ios::out);
	outputFile << ladderNum << std::endl;
	pGrid->Save(outputFile, 1);
	outputFile << snakeNum << std::endl;
	pGrid->Save(outputFile, 2);
	outputFile << cardNum << std::endl;
	pGrid->Save(outputFile, 3);
	outputFile << coinNum << std::endl;
	pGrid->Save(outputFile, 4);
	outputFile.close();

}

//Mohamed Shams