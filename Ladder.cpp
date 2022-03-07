#include "Ladder.h"
#include "Grid.h"
#include "GameObject.h"
#include <fstream>

//done by noha
Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	//Done by noha just checking the position of the ladder
	//if (startCellPos.HCell() == endCellPos.HCell() && endCellPos.VCell() > startCellPos.VCell()) {
	this->endCellPos = endCellPos;
	this->startCellPos = startCellPos;
	///TODO: Do the needed validation
}


void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	//    Review the "pGrid" functions and decide which function can be used for that

}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}
// (done by noha)getting startcell
CellPosition Ladder::GetStartPosition() const {
	return startCellPos;
}
Ladder::~Ladder()
{
}
void Ladder::SaveToFile(ofstream& output, int obj) {
	if (obj == 1) {
		//GameObject::SaveToFile(output, obj);
		int start = this->GetStartPosition().GetCellNum();
		int end = this->endCellPos.GetCellNum();
		output << start << " " << end << std::endl;
	}
}
void Ladder::Get_ladderPtr(int num, ifstream& inputFile, Grid* newGrid) {
	int i = 0;
	while (i < num) {
		int startposition = 0;
		int endposition = 0;
		inputFile >> startposition >> endposition;
		Ladder* ptrLadder = new Ladder(CellPosition(startposition), CellPosition(endposition));
		newGrid->AddObjectToCell(ptrLadder);
		i++;
		
	}

}
