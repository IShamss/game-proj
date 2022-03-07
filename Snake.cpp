#include "Snake.h"
#include "Grid.h"
#include "GameObject.h"
#include <fstream>
#include "CellPosition.h"
//done by noha
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	//Done by noha just checking the position of the Snake
	//if (startCellPos.HCell() == endCellPos.HCell() && endCellPos.VCell() < startCellPos.VCell()) {
	this->endCellPos = endCellPos;
	this->startCellPos = startCellPos;
	///TODO: Do the needed validation
}


void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
	

}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a Snake. Click to continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	//    Review the "pGrid" functions and decide which function can be used for that

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

//(done by noha)getting startcell
CellPosition Snake::GetStartPosition() const {
	return startCellPos;
}
Snake::~Snake()
{
}
void Snake::SaveToFile(ofstream& output, int obj) {
	if (obj == 2) {
		//GameObject::SaveToFile(output, obj);
		//1
		int start = this->GetStartPosition().GetCellNum();
		int end = this->GetEndPosition().GetCellNum();
		////2
		//int start = this->startCellPos.GetCellNum();
		//int end = this->endCellPos.GetCellNum();
		////3
		//int start = this->GetStartPosition().GetCellNumFromPosition(this->GetStartPosition());
		//int end = this->GetEndPosition().GetCellNumFromPosition(this->GetEndPosition());
		////4
		//int start = this->startCellPos.GetCellNumFromPosition(this->startCellPos);
		//int end = this->endCellPos.GetCellNumFromPosition(this->endCellPos);
		output << start << " " << end << std::endl;
	}
}
void Snake::Get_SnakePtr(int num, ifstream& inputFile, Grid* newGrid) {
	int i = 0;
	while (i < num) {
		int startposition = 0;
		int endposition = 0;
		inputFile >> startposition >> endposition;

		Snake* ptrSnake = new Snake(CellPosition(startposition), CellPosition(endposition));
		newGrid->AddObjectToCell(ptrSnake);
		i++;
	}
}