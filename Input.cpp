#include "Input.h"

#include "Output.h"

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetString(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO) const
{

	///TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()

	string n = Input::GetString(pO); // (done by noha)take the input integer from the function GetString and assigned it in n
	return stoi(n);//(done by noha) stoi converts string n to the user input integer then I return it

	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)


}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				//((Done by noha)design cases)
			case ITM_ADD_LADDER: return ADD_LADDER;
			case ITM_ADD_SNAKE: return ADD_SNAKE;
			case ITM_ADD_CARD: return ADD_CARD;
			case ITM_EXIT: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;
			case ITM_Add_Coin_Set:return Add_Coin_Set;
			case ITM_Copy_Card_Or_Coins:return Copy_Card_Or_Coins;
			case ITM_Cut_Card_Or_Coins:return Cut_Card_Or_Coins;
			case ITM_Paste:return Paste;
			case ITM_Delete_Game_Object:return Delete_Game_Object;
			case ITM_Save_Grid:return Save_Grid;
			case ITM_Open_Grid:return Open_Grid;

				///TODO: Add cases for the other items of Design Mode




			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		//((Done by noha)same as we done in design mode ,here is the cases for play mode) 
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder) {

			case ITM_ROLL_DICE:return ROLL_DICE;
			case ITM_Input_Dice_Value:return Input_Dice_Value;
			case ITM_OfferMortgage:return OfferMortgage;
			case ITM_AcceptMortage: return AcceptMortage;
			case ITM_ReturnMortage:return ReturnMortage;
			case ITM_SellCity:return Sell_City;
			case ITM_New_Game: return New_Game;
			case ITM_SWITCH_TO_DESIGN_MODE:return TO_DESIGN_MODE;
			case ITM_Exit: return EXIT;

			default: return EMPTY;	// A click on empty place in toolbar
			}
		}
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x, y;
	this->GetPointClicked(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if (UI.InterfaceMode == MODE_DESIGN)
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			int y2 = y - UI.ToolBarHeight;
			
			int vcell=-1;

			while (y2 > 0)
			{
				y2 -= UI.CellHeight;
				vcell++;
			}

			cellPos.SetVCell(vcell);

			int x2 = x;

			int hcell = -1;

			while (x2 > 0)
			{
				x2 -= UI.CellWidth;
				hcell++;
			}

			cellPos.SetHCell(hcell);
		}
	}
	else
	{
		if (y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			int y2 = y - UI.ToolBarHeight;

			int vcell = -1;

			while (y2 > 0)
			{
				y2 -= UI.CellHeight;
				vcell++;
			}

			cellPos.SetVCell(vcell);

			int x2 = x;

			int hcell = -1;

			while (x2 > 0)
			{
				x2 -= UI.CellWidth;
				hcell++;
			}

			cellPos.SetHCell(hcell);
		}
	}
	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 
