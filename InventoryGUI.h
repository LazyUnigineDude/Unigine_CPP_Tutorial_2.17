#pragma once
#include "DatabaseController.h"
#include "InventoryMaker.h"
#include <vector>
#include <string>
#include <map>

struct InventoryGUI {

public:
	InventoryGUI() = default;
	InventoryGUI(InventoryMaker* Inventory);
	void Hide();
	void Show();
	void Shutdown();

private:
	void DeleteGrid();
	void CreateBackground();
	void CreateGrid();

	void OnHover(Unigine::WidgetPtr Widget);
	void OnLeave(Unigine::WidgetPtr Widget);
	void OnClick(Unigine::WidgetPtr Widget);
	void OnDrop(Unigine::WidgetPtr Widget1, Unigine::WidgetPtr Widget2);
	Unigine::GuiPtr GUI;
	Unigine::WidgetCanvasPtr BackGround;
	std::vector<Unigine::WidgetPtr> ImageList, TextList;
	std::map<Unigine::WidgetPtr, int> Map;
	Unigine::WidgetGridBoxPtr Grid, TextGrid;

	InventoryMaker* Inventory;
};

inline InventoryGUI::InventoryGUI(InventoryMaker* Inventory )  {
	this->Inventory = Inventory; 
	CreateBackground();
}

inline void InventoryGUI::Hide() {

	GUI = Unigine::Gui::getCurrent();
	if (GUI->isChild(BackGround)) { GUI->removeChild(BackGround); }
	if (GUI->isChild(Grid)) { GUI->removeChild(Grid); }
	if (GUI->isChild(TextGrid)) { GUI->removeChild(TextGrid); 	DeleteGrid(); }
}

inline void InventoryGUI::Show() {

	GUI = Unigine::Gui::getCurrent();
	CreateGrid();
	if (!GUI->isChild(BackGround)) GUI->addChild(BackGround, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	if (!GUI->isChild(Grid)) GUI->addChild(Grid, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	if (!GUI->isChild(TextGrid)) GUI->addChild(TextGrid, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
}


inline void InventoryGUI::DeleteGrid() {

	for (auto Image : ImageList) {
		Grid->removeChild(Image);
		Image->deleteLater();
	}

	for (auto Text : TextList) {
		TextGrid->removeChild(Text);
		Text->deleteLater();
	}
	Map.clear();
	ImageList.clear(); TextList.clear();
	Grid->deleteLater(); TextGrid->deleteLater();
}


inline void InventoryGUI::CreateBackground() {

	GUI = Unigine::Gui::getCurrent();
	BackGround = Unigine::WidgetCanvas::create();
	int BNum = BackGround->addPolygon();
	int x = 500, y = 300;
	Unigine::Math::vec3 Point[] = {
		Unigine::Math::vec3(-x,-y,0),
		Unigine::Math::vec3( x,-y,0),
		Unigine::Math::vec3( x, y,0),
		Unigine::Math::vec3(-x, y,0),
	};
	BackGround->addPolygonPoint(BNum, Point[0]);
	BackGround->addPolygonPoint(BNum, Point[1]);
	BackGround->addPolygonPoint(BNum, Point[2]);
	BackGround->addPolygonPoint(BNum, Point[3]);
	BackGround->setPolygonColor(BNum, Unigine::Math::vec4(0,0,0,0.8));
	BackGround->setPosition((GUI->getWidth() / 2) - (x/2), (GUI->getHeight() / 2) - (y/2) );
}

inline void InventoryGUI::CreateGrid() {

	Unigine::WidgetSpritePtr Image;
	Grid = Unigine::WidgetGridBox::create(6, 5, 5);
	TextGrid = Unigine::WidgetGridBox::create(6, 5, 5);

	ImageList.reserve(Inventory->ArraySize());
	TextList.reserve(Inventory->ArraySize());
	DatabaseController* Database = Database->GetDatabase();

	for (int i = 0; i < Inventory->ArraySize(); i++) {

		int _ID = Inventory->GetItem(i).x;
		Unigine::ImagePtr _image = Unigine::Image::create();
		_image->load(Database->GetImagePath(_ID));

		Image = Unigine::WidgetSprite::create();
		Image->setImage(_image);
		Image->setWidth(64);
		Image->setHeight(64);

		if (_ID != 0) {
			Image->addCallback(GUI->ENTER, Unigine::MakeCallback(this, &InventoryGUI::OnHover));
			Image->addCallback(GUI->LEAVE, Unigine::MakeCallback(this, &InventoryGUI::OnLeave));
			Image->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &InventoryGUI::OnClick));
		}
		Image->addCallback(GUI->DRAG_DROP, Unigine::MakeCallback(this, &InventoryGUI::OnDrop));

		Map[Image] = i;
		ImageList.push_back(Image);
		Grid->addChild(Image);
			
		int _Amount = Inventory->GetItem(i).y;
		Unigine::WidgetLabelPtr _Text = Unigine::WidgetLabel::create();
		if(_ID != 0) _Text->setText(std::to_string(_Amount).c_str());
		_Text->setFontSize(12);
		_Text->setFontColor(Unigine::Math::vec4_white);
		_Text->setWidth(64);
		_Text->setHeight(64);

		TextList.push_back(_Text);
		TextGrid->addChild(_Text);
	}

		Grid->setPosition((GUI->getWidth() / 2) - (204), (GUI->getHeight() / 2) - 140);
	TextGrid->setPosition((GUI->getWidth() / 2) - (204), (GUI->getHeight() / 2) - 140);
}

inline void InventoryGUI::Shutdown() {
	DeleteGrid();
	BackGround->deleteLater();
}


////////////////////////////////////////////

inline void InventoryGUI::OnHover(Unigine::WidgetPtr Widget) {

	Unigine::WidgetSpritePtr _Image = Unigine::checked_ptr_cast<Unigine::WidgetSprite>(Widget);
	_Image->setColor(Unigine::Math::vec4_green);
}

inline void InventoryGUI::OnLeave(Unigine::WidgetPtr Widget) {

	Unigine::WidgetSpritePtr _Image = Unigine::checked_ptr_cast<Unigine::WidgetSprite>(Widget);
	_Image->setColor(Unigine::Math::vec4_white);
}

inline void InventoryGUI::OnClick(Unigine::WidgetPtr Widget) {

	int Pos = 0;
	if (Map.contains(Widget)) { Pos = Map[Widget]; }
	DatabaseController* Database = Database->GetDatabase();

	int ID = Inventory->GetItem(Pos).x, 
		Amount = Inventory->GetItem(Pos).y, 
		Value = Database->GetValue(ID);
	const char* Name = Database->GetName(ID);
	Unigine::Log::message("Name: %s  ID: %d  Amount: %d  Value: %d\n", Name, ID, Amount, Value);

}

inline void InventoryGUI::OnDrop(Unigine::WidgetPtr Widget1, Unigine::WidgetPtr Widget2) {
	
	int Pos1, Pos2;
	if (Map.contains(Widget1)) { Pos1 = Map[Widget1]; }
	if (Map.contains(Widget2)) { Pos2 = Map[Widget2]; }

	Inventory->Swap(Pos2, Pos1);
	Hide();
	Show();
}