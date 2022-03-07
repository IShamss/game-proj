
#pragma once

#include "GameObject.h"
#include<fstream>
//done by noha
class Ladder : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the ladder's End Cell Position
	CellPosition startCellPos; //(done by noha) here is the ladder's start cell

public:

	Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const;// A getter for the endCellPos data member
	CellPosition GetStartPosition() const; //(done by noha)A getter for the startcellpos
	void Get_ladderPtr(int num, ifstream& inputFile, Grid* newGrid);
	virtual ~Ladder(); // Virtual destructor
	void SaveToFile(ofstream&, int);
};

