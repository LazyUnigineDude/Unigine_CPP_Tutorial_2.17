#pragma once
#include "InventoryMaker.h"

struct InventoryInteractor {

public:
	InventoryInteractor() = default;
	InventoryInteractor(Unigine::PlayerPtr Camera, int MaskNum);
	bool DetectItem();
	Unigine::Math::ivec2 GetItem();
	void Shutdown();

private:
	int MaskNum;
	Unigine::PlayerPtr Camera;
	Unigine::WidgetLabelPtr Label;
	Unigine::WorldIntersectionPtr Intersection;
	Unigine::ObjectPtr Item;
	Unigine::Math::ivec2 _item;
	Unigine::GuiPtr GUI;
};

inline InventoryInteractor::InventoryInteractor(Unigine::PlayerPtr Camera, int MaskNum) { 
	
	this->Camera = Camera;
	this->MaskNum = MaskNum; 
	Intersection = Unigine::WorldIntersection::create();

	GUI = Unigine::Gui::getCurrent();
	Label = Unigine::WidgetLabel::create();
	Label->setFontOutline(1);
	Label->setFontSize(21);
	GUI->addChild(Label, GUI->ALIGN_CENTER | GUI->ALIGN_OVERLAP);
	Label->setPosition(Label->getPositionX() - 50, Label->getPositionY() + 50);
}

inline bool InventoryInteractor::DetectItem() {

	Unigine::Math::Vec3 CamViewDir = Unigine::Math::Vec3(Camera->getWorldDirection() * 10) + Camera->getWorldPosition();
	Unigine::ObjectPtr _Item = Unigine::World::getIntersection(
		Camera->getWorldPosition(),
		CamViewDir,
		MaskNum,
		Intersection
	);

	if (_Item) {

		if (Item != _Item) {

			_item = Unigine::Math::ivec2(
				_Item->getProperty(0)->getParameterPtr(0)->getValueInt(),
				_Item->getProperty(0)->getParameterPtr(1)->getValueInt());

			DatabaseController* Database = Database->GetDatabase();
			Item = _Item;

			std::string _String = "Item: ";
			_String += Database->GetName(_item.x);
			_String += "\nAmount: ";
			_String += std::to_string(_item.y);

			Label->setText(_String.c_str());
		}
		return 1;
	}

	Item = nullptr;
	Label->setText(" ");
	return 0;
}

inline Unigine::Math::ivec2 InventoryInteractor::GetItem() {

	Item = nullptr;
	if (DetectItem()) {
		Unigine::Log::message("%d %d\n", _item.x, _item.y);
		Item->deleteLater();
		return _item;
	}
	return Unigine::Math::ivec2_zero;
}

inline void InventoryInteractor::Shutdown() {

	GUI = Unigine::Gui::getCurrent();
	if (GUI->isChild(Label)) { GUI->removeChild(Label); Label->deleteLater(); }
}
