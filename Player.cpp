#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(1), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	chosenInCard4 = 0;//noha
	stop = 0;//noha
	justRolledDiceNum = 0;
	countFreeze = 0;
	BenefitAll = 0;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

int Player::GetPlayerNum() const
{
	return playerNum;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	//done by noha
	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;

	//done by noha
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);

}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{//(done by noha) a validation in the  play's wallet less than or equal zero the player can't move
	if (GetWallet() < 0 || GetWallet() == 0) {
		return;
	}
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	if (freeze == true && freezeTurns > countFreeze)
	{
		countFreeze++;
		return;
	}

	if (freeze==true && freezeTurns == countFreeze)
	{
		freeze = false;
		countFreeze = 0;
		return;
	}
	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount % 3 == 0) {
		this->SetWallet(this->GetWallet() + (diceNumber * 10));
		turnCount = 0;
		return;
	}
	// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum = diceNumber;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos;
	pos = this->GetCell()->GetCellPosition();
	if (stop == 1 || chosenInCard4) {
		//pGrid->UpdatePlayerCell(this, 0);
		pos.AddCellNum(0);
		chosenInCard4 = 0;
	}
	else {
		pos.AddCellNum(diceNumber);
	}

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, pos);

	this->stepCount = pos.GetCellNum();
	// 6- Apply() the game object of the reached cell (if any)
	if (this->GetCell()->GetGameObject()) {
		this->GetCell()->GetGameObject()->Apply(pGrid, this);
	}
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (this->GetCell()->GetCellPosition().GetCellNum() >= (NumHorizontalCells * NumVerticalCells)) {
		pGrid->SetEndGame(true);
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::SetTurnCount(int turn)
{
	this->turnCount = turn;
}

int Player::GetStepCount() const
{
	return stepCount;
}

int Player::GetDiceValue()const {
	return justRolledDiceNum;
}
//(done by noha) implementing setter and getter for stop
void Player::SetStop(bool s) {
	stop = s;
}
bool Player::GetStop() {
	return stop;
}
void Player::IsChosen() {
	//done by noha
	chosenInCard4 = 1;
}
int Player::GetPlayerNo() {
	//done by noha
	return playerNum;
}
void Player::setFreeze(bool x, int n) {
	freeze = true;
	freezeTurns = n;
}
void Player::BenefitALL(int y) {

}

void Player::SetStepCount(int x)
{
	stepCount = x;
}