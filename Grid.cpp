#include "Grid.h"
#include <fstream>
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Cairo.h"
#include "Snake.h"
#include "CoinSet.h"
#include "Luxor.h"
#include "Hurghada.h"
#include "Alexandria.h"
#include "Aswan.h"
#include "CellPosition.h"
#include "TakeCityCard.h"
#include "DecWalletCard_1.h"
#include "AcceptMortgage.h"
#include "LoseCityCard.h"
#include "ReturnMortgagedCard.h"
#include "PreventCard_4.h"
#include "FireCard_5.h"
#include "FreezeCard.h"
#include "NextCard_2.h"
#include "BenefitAllCard.h"
#include "BackwardCard_3.h"
#include "CoinSet.h"


Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;
	coinClipboard = NULL;
	fromcopy = false;
	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		GameObject* g1 = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		delete g1;
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);

	}
}

void Grid::Removeobjectfromcellnodelete(const CellPosition& pos)
{
	CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

// ========= Setters and Getters Functions =========


Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card* pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card* Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player* Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Cell* Grid::GetCell(CellPosition& cpos) const
{
	return CellList[cpos.VCell()][cpos.HCell()];
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			if (CellList[i][j]->HasLadder()) {
				return CellList[i][j]->HasLadder();
			}

			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			//done by noha
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		///TODO: Add the code that draws the CoinSet game objects
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCoinSet(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


void Grid::SetcurrPlayerNumber(int curr)
{
	this->currPlayerNumber = curr;
}

int Grid::GetcurrPlayerNumber()
{
	return currPlayerNumber;
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}

int Grid::ladderCount() {
	int sum = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder() != NULL && CellList[i][j]->HasCoinSet() == NULL)
				sum++;
		}
	}
	return sum;
}

int Grid::snakeCount() {
	int sum = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasSnake() != NULL && CellList[i][j]->HasCoinSet() == NULL)
				sum++;
		}
	}
	return sum;
}
int Grid::cardCount() {
	int sum = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasCard() != NULL && CellList[i][j]->HasCoinSet() == NULL)
				sum++;
		}
	}
	return sum;
}

int Grid::coinCount() {
	int sum = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasCoinSet() != NULL)
				sum++;
		}
	}
	return sum;
}

void Grid::SetCoinClipboard(CoinSet* coinSet) // to be used in copy/cut
{

	this->coinClipboard = coinSet;
}


CoinSet* Grid::GetCoinClipboard() const // to be used in paste
{
	return coinClipboard;
}

Snake* Grid::GetNextSnake(const CellPosition& position)
{
	//done by noha

	int startH = position.HCell();
	for (int i = position.VCell(); i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasSnake()) {
				return CellList[i][j]->HasSnake();
			}





		}
		startH = 0;
	}
	return NULL;
}

CoinSet* Grid::GetNextCoinSet(const CellPosition& position)
{
	//done by noha
	int startH = position.HCell();
	for (int i = position.VCell(); i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasCoinSet()) {
				return CellList[i][j]->HasCoinSet();
			}





		}
		startH = 0;
	}
	return NULL;
}

Card* Grid::GetNextCard(const CellPosition& position)
{
	//done by noha
	int startH = position.HCell() + 1;
	for (int i = position.VCell(); i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{

			if (CellList[i][j]->HasCard()) {
				return CellList[i][j]->HasCard();
			}





		}
		startH = 0;
	}
	return NULL;
}

Player*& Grid::GetClickedPlayer(CellPosition  pos) {
	for (int i = 0; i < 4; i++) {
		if (PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() == pos.GetCellNum()) {
			return PlayerList[i];
		}

	}

}

void Grid::firing(Player* curP) {
	//done by noha
	for (int i = 0; i < 4; i++) {
		if ((curP->GetCell()->GetCellPosition().VCell() ==
			PlayerList[i]->GetCell()->GetCellPosition().VCell()) || (curP->GetCell()->GetCellPosition().HCell() ==
				PlayerList[i]->GetCell()->GetCellPosition().HCell())) {
			if (PlayerList[i]->GetPlayerNo() != curP->GetPlayerNo()) {
				PlayerList[i]->Move(this, -1 * (PlayerList[i]->GetCell()->GetCellPosition().GetCellNumFromPosition(PlayerList[i]->GetCell()->GetCellPosition()) - 1));
				PlayerList[i]->SetWallet((PlayerList[i]->GetWallet()) / 2);
			}
		}
	}

}
void Grid::FreezePlayers(Player* currentPlayer, bool y, int n) {
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		if (PlayerList[i] != currentPlayer) {
			int x = PlayerList[i]->GetCell()->GetCellPosition().GetCellNum();
			if (y == true) {
				if (x % 2 == 0) {
					PlayerList[i]->setFreeze(y, n);
				}
			}
			else if (y == false) {
				if (x % 2 != 0) {
					PlayerList[i]->setFreeze(y, n);
				}
			}
		}

	}
}

void Grid::MovePlayersBackWard(Player* pCurrPlayer) {
	//done by noha
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		if (PlayerList[i] != pCurrPlayer) {
			PlayerList[i]->Move(this, -1 * (pCurrPlayer->GetDiceValue()));
		}
	}
}

void Grid::Resetcity()
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->HasCairo() != NULL)
			{
				Cairo* tempcard = CellList[i][j]->HasCairo();
				tempcard->Mortgagedto = NULL;
				tempcard->owner = NULL;
				tempcard->Upformortgage = false;
				tempcard->Setbought(false);
			}

			if (CellList[i][j]->HasAlexandria() != NULL)
			{
				Alexandria* tempcard = CellList[i][j]->HasAlexandria();
				tempcard->Mortgagedto = NULL;
				tempcard->owner = NULL;
				tempcard->Upformortgage = false;
				tempcard->Setbought(false);
			}

			if (CellList[i][j]->HasAswan() != NULL)
			{
				Aswan* tempcard = CellList[i][j]->HasAswan();
				tempcard->MortgagedTo = NULL;
				tempcard->owner = NULL;
				tempcard->Upformortgage = false;
				tempcard->Setbought(false);
			}

			if (CellList[i][j]->HasLuxor() != NULL)
			{
				Luxor* tempcard = CellList[i][j]->HasLuxor();
				tempcard->Mortgagedto = NULL;
				tempcard->owner = NULL;
				tempcard->Upformortgage = false;
				tempcard->Setbought(false);
			}

			if (CellList[i][j]->HasHurghada() != NULL)
			{
				Hurghada* tempcard = CellList[i][j]->HasHurghada();
				tempcard->Mortgagedto = NULL;
				tempcard->owner = NULL;
				tempcard->Upformortgage = false;
				tempcard->Setbought(false);
			}

		}
	}
}

void Grid::ApplyforsameCairo(Cairo* x)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->HasCairo() != NULL)
			{
				Cairo* tempcard = CellList[i][j]->HasCairo();
				tempcard->ApplyforCairo(x, tempcard);
			}
		}
	}
}

void Grid::ApplyforsameLuxor(Luxor* x)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->HasLuxor() != NULL)
			{
				Luxor* tempcard = CellList[i][j]->HasLuxor();
				tempcard->ApplyforLuxor(x, tempcard);
			}
		}
	}
}

void Grid::ApplyforsameAlex(Alexandria* x)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->HasAlexandria() != NULL)
			{
				Alexandria* tempcard = CellList[i][j]->HasAlexandria();
				tempcard->ApplyforAlex(x, tempcard);
			}
		}
	}
}

void Grid::ApplyforsameHurg(Hurghada* x)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->HasHurghada() != NULL)
			{
				Hurghada* tempcard = CellList[i][j]->HasHurghada();
				tempcard->ApplyforHurg(x, tempcard);
			}
		}
	}
}

void Grid::ApplyforsameAswan(Aswan* x)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->HasAswan() != NULL)
			{
				Aswan* tempcard = CellList[i][j]->HasAswan();
				tempcard->ApplyforAswan(x, tempcard);
			}
		}
	}
}

void Grid::Setfromcopy(bool x)
{
	fromcopy = x;
}

bool Grid::Getfromcopy()
{
	return fromcopy;
}
void Grid::Save(ofstream& output, int obj) {
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject() != NULL) {
				CellList[i][j]->GetGameObject()->SaveToFile(output, obj);
			}
		}
	}
}
void Grid::RemoveAllObjects() {
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject() != NULL) {
				RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
			}
		}
	}
}
void Grid:: LoadGameObjects(int num, char type, ifstream& inputFile, Grid* newGrid) {
	if (type == 'l') {
		Ladder* ptrLadder = new Ladder(0,0);
		ptrLadder->Get_ladderPtr(num, inputFile, newGrid);
	}
	else if (type == 's') {
		Snake* ptrSnake = new Snake(0, 0);
		ptrSnake->Get_SnakePtr(num, inputFile, newGrid);
	
	}
	else if (type == 'c') {
		Card* ptrCard = new Card(0);
		ptrCard->Get_CardPtr(num, inputFile, newGrid);
	}
	else {
		CoinSet* ptrCoin = new CoinSet(0,0);
		ptrCoin->getCoinPtr(num, inputFile, newGrid);
	}
}