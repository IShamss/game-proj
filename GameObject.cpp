#include "GameObject.h"

#include <fstream>
GameObject::GameObject(const CellPosition& pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

GameObject::~GameObject()
{
}
void GameObject::SaveToFile(ofstream& output, int type)
{
	int cellNum = position.GetCellNum();
	output << cellNum;
}