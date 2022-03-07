
#pragma once
#include <fstream>
#include "GameObject.h"
//done by noha
class Snake : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the Snake's "Start Cell Position"

	CellPosition endCellPos; // here is the Snake's End Cell Position
	CellPosition startCellPos; //(done by noha) here is the Snake's start cell

public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a Snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the Snake by moving player to Snake's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	CellPosition GetStartPosition() const; //(done by noha)A getter for the startcellpos
	virtual ~Snake(); // Virtual destructor
	void Get_SnakePtr(int num, ifstream& inputFile, Grid* newGrid);
	virtual void SaveToFile(ofstream& output, int obj);
};
