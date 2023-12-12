#include "Interactor.h"
REGISTER_COMPONENT(Interactor)

void Interactor::Init(Unigine::PlayerPtr Camera) {

	Intersection = Unigine::WorldIntersection::create();
	this->Camera = Camera;

	GUI = Unigine::Gui::getCurrent();
	Label = Unigine::WidgetLabel::create();
	Label->setFontOutline(1);
	Label->setFontSize(21);
	GUI->addChild(Label, GUI->ALIGN_CENTER | GUI->ALIGN_OVERLAP);
	Label->setPosition(Label->getPositionX() - 50, Label->getPositionY() + 50);
}

bool Interactor::Update() {

	Unigine::ObjectPtr IObj = Unigine::World::getIntersection(
		Camera->getWorldPosition(),
		Camera->getWorldPosition() + Unigine::Math::Vec3((Camera->getWorldDirection() * 10)),
		MaskNum,
		Intersection
	);

	if (IObj) {

		if (Item != IObj) {

			_item = Unigine::Math::ivec2(
				IObj->getProperty(0)->getParameterPtr(0)->getValueInt(),
				IObj->getProperty(0)->getParameterPtr(1)->getValueInt());

			DatabaseController* Database = Database->GetDatabase();
			std::string _String;
			Item = IObj;
			Type = Database->GetItemType(_item.x);

			switch (Type) {
			case DatabaseController::DEFAULT:
				_String += "Item: ";
				_String += Database->GetName(_item.x);
				_String += "\nAmount: ";
				_String += std::to_string(_item.y);
				break;
			case DatabaseController::WEAPON:
				_String += "Item: ";
				_String += Database->GetName(_item.x);
				_String += "\nAmmo: ";
				_String += std::to_string(_item.y);
				break;
			case DatabaseController::TRIGGER:
				_String += "Interact";
				break;
			default:
				break;
			}
			Label->setText(_String.c_str());
		}
		return 1;
	}

	Item = nullptr;
	Label->setText(" ");
	return 0;
}

Unigine::Math::ivec2 Interactor::GetItemFromDetection() {
	
	Item = nullptr;
	if (Update()) {
		Unigine::Log::message("%d %d\n", _item.x, _item.y);
		if(Type != DatabaseController::TRIGGER) Item->deleteLater();
		else {
			DoorOpener* Door = getComponent<DoorOpener>(Item->getChild(0));
			if (Door) Door->OpenDoor();
		}
		return _item;
	}
	return Unigine::Math::ivec2_zero;
}
void Interactor::Shutdown() {

	Intersection->deleteLater(); 
	GUI = Unigine::Gui::getCurrent();
	if (GUI->isChild(Label)) { GUI->removeChild(Label); Label->deleteLater(); }
}
