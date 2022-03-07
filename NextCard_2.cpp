#include "NextCard_2.h"
#include<iostream>
#include"Ladder.h"
#include"Snake.h"
#include"Card.h"
#include"CoinSet.h"
using namespace std;
//done by noha
NextCard_2::NextCard_2(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2;
}

NextCard_2::~NextCard_2(void)
{
}

void NextCard_2::ReadCardParameters(Grid* pGrid)
{


	Input* ptrIN = pGrid->GetInput();
	Output* ptrOUT = pGrid->GetOutput();

	ptrOUT->PrintMessage("New NextCard_2... Enter type 1 for ladder, 2 for snake 3 for coinset 4 for card");
	//pGrid->GetCurrentPlayer()->GetCell();
	type = ptrIN->GetInteger(ptrOUT);

	ptrOUT->ClearStatusBar();
}

void NextCard_2::Apply(Grid* pGrid, Player* pPlayer)
{
	bool x = false;
	CellPosition position1;
	Card::Apply(pGrid, pPlayer);
	if (type == 1) {
		Ladder* ptrladder = pGrid->GetNextLadder(GetPosition());
		if (ptrladder == NULL) {
			Ladder* ptrladder = pGrid->GetNextLadder(position1.GetCellPositionFromNum(1));
		}
		/*else if(ptrladder == NULL) {
			return;

		 }*/
		if (ptrladder != NULL)
		{
			position1 = ptrladder->GetPosition();
			pGrid->UpdatePlayerCell(pPlayer, position1);
			if ((pPlayer->GetCell()->GetCellPosition()).GetCellNum() >= 99) {
				pGrid->SetEndGame(1);
			}
			if (pPlayer->GetCell()->GetGameObject()) {
				pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
			}
		}

	}
	else if (type == 2) {
		Snake* ptrSnake = pGrid->GetNextSnake(GetPosition());
		if (ptrSnake == NULL) {
			Snake* ptrSnake = pGrid->GetNextSnake(position1.GetCellPositionFromNum(1));
		}
		/*else if (ptrSnake == NULL) {
			return;

		}*/
		if (ptrSnake != NULL)
		{
			position1 = ptrSnake->GetPosition();
			pGrid->UpdatePlayerCell(pPlayer, position1);
			if ((pPlayer->GetCell()->GetCellPosition()).GetCellNum() >= 99) {
				pGrid->SetEndGame(1);
			}
			if (pPlayer->GetCell()->GetGameObject()) {
				pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
			}
		}
	}
	else if (type == 3) {
		CoinSet* ptrCoinSet = pGrid->GetNextCoinSet(GetPosition());
		if (ptrCoinSet == NULL) {
			CoinSet* ptrCoinSet = pGrid->GetNextCoinSet(position1.GetCellPositionFromNum(1));
		}
		/*else if (ptrCoinSet == NULL) {
			return;

		}*/
		if (ptrCoinSet != NULL)
		{
			position1 = ptrCoinSet->GetPosition();
			pGrid->UpdatePlayerCell(pPlayer, position1);
			if ((pPlayer->GetCell()->GetCellPosition()).GetCellNum() >= 99) {
				pGrid->SetEndGame(1);
			}
			if (pPlayer->GetCell()->GetGameObject()) {
				pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
			}
		}
	}
	else if (type == 4) {
		Card* ptrCard = pGrid->GetNextCard(GetPosition());
		if (ptrCard == NULL) {
			Card* ptrCard = pGrid->GetNextCard(position1.GetCellPositionFromNum(1));
		}
		/*else if (ptrCard == NULL) {
			return;

		}*/
		if (ptrCard != NULL)
		{
			position1 = ptrCard->GetPosition();
			if (position1.GetCellNum() != GetPosition().GetCellNum())
				pGrid->UpdatePlayerCell(pPlayer, position1);
			if ((pPlayer->GetCell()->GetCellPosition()).GetCellNum() >= 99) {
				pGrid->SetEndGame(1);
			}
			if (pPlayer->GetCell()->GetGameObject()) {
				pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
			}
		}
	}
}

