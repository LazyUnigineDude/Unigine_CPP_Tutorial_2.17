#include "InventoryController.h"
REGISTER_COMPONENT(InventoryController)

void InventoryController::Init(){

	Inventory = InventoryMaker(InventoryNode->getProperty(0)->getParameterPtr(0));
	GUI = InventoryGUI(&Inventory);
}

void InventoryController::Update(){

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_Y)) {
		GUI.Show();
	}

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_U)) {
		GUI.Hide();
	}
}

void InventoryController::Shutdown() {
	GUI.Shutdown();
}
