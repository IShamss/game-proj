#include "ApplicationManager.h"

#include "Grid.h"
#include "AddLadderAction.h"
#include "AddCardAction.h"
#include "RollDiceAction.h"
#include "Delete.h"
#include "NewGame.h"
#include "ToDesignMode.h"
#include "ToPlayMode.h"
#include "InputDice.h"
#include "OfferMortgage.h"
#include "AcceptMortgage.h"
#include "ReturnMortgage.h"
#include "AddSnakeAction.h"
#include "AddCoinSet.h"
#include "CopyAction.h"
#include "CutAction.h"
#include "PasteAction.h"
#include "SaveGridAction.h"
#include "SellCity.h"
#include"LoadGridAction.h"

///TODO: Add #include for all action types

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;

	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case Add_Coin_Set:
		pAct = new AddCoinSetAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case Copy_Card_Or_Coins:
		pAct = new CopyAction(this);
		break;

	case Cut_Card_Or_Coins:
		pAct = new CutAction(this);
		break;

	case Paste:
		pAct = new PasteAction(this);
		break;

	case Save_Grid:
		pAct = new SaveGridAction(this);
		break;
	case Open_Grid:
		pAct = new LoadGridAction(this);
		break;



	case EXIT:
		break;

	case Delete_Game_Object:
		pAct = new Delete(this);
		break;

	case TO_PLAY_MODE:
		pAct=new ToPlayMode(this) ; ///TODO: temporary till you made its action class (CHANGE THIS LATTER)
		break;

	case ROLL_DICE:
		// create an object of RollDiceAction here
		pAct = new RollDiceAction(this);
		break;

	case TO_DESIGN_MODE:
		pAct=new ToDesignMode (this); //TODO: temporary till you made its action class (CHANGE THIS LATTER)
		break;

	case New_Game:
		pAct = new NewGame(this);
		break;

	case Input_Dice_Value:
		pAct = new InputDice(this);
		break;

	case OfferMortgage:
		pAct = new Offer_Mortgage(this);
		break;

	case AcceptMortage:
		pAct = new Accept_Mortgage(this);
		break;

	case ReturnMortage:
		pAct = new Return_Mortgage(this);
		break;

	case Sell_City:
		pAct = new SellCity(this);
		break;

	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}