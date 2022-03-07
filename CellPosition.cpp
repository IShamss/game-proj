#include "CellPosition.h"
#include "UI_Info.h"
#include <math.h>

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	// the vertical cells are from 0 to 8 and if they are less than 0 or greater than 8 then the position is invalid
	if (v <= 8 && v > -1) {
		this->vCell = v;
		return true;
	}
	//once the return statement is reached the function exits automatically
	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	//same as the validation in the vertical cells but horizontal cells are from 0 to 10
	if (h <= 10 && h > -1) {
		this->hCell = h;
		return true;
	}

	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	//validating the current cell position
	if (vCell <= 8 && vCell > -1 && hCell <= 10 && hCell > -1) {
		return true;
	}

	return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	//calculating the cell number given its vcell and hcell
	int cellNum = (8 - cellPosition.VCell()) * 11 + (cellPosition.HCell() + 1);

	return cellNum; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	int vcell;
	if (cellNum % 11 == 0)
	{
		vcell = 9 - (cellNum/11) ;
	}
	else
	{
		vcell=9 - floor(cellNum / 11) - 1;
	}
	int hcell;
	if (cellNum % 11 == 0) {
		hcell = 10;
	}
	else {
		hcell = (cellNum % 11) - 1;
	}
	//setting the attributes of the object to the values calculated from the cell number
	position.SetVCell(vcell);
	position.SetHCell(hcell);


	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	//return the newly created object
	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file
	//adding the argument to the cell number of the current instance and putting it in a new variable
	int newCellNum = this->GetCellNum() + addedNum;
	//making a new object having the new cell number
	CellPosition p1 = this->GetCellPositionFromNum(newCellNum);
	//setting the cell position of the current instance to the cell position of the object with the new cell number
	this->SetHCell(p1.HCell());
	this->SetVCell(p1.VCell());
	//at the end of this scope the newly created object is destroyed

	// Note: this function updates the data members (vCell and hCell) of the calling object

}
//Mohamed Shams