#include "InventoryController.h"
REGISTER_COMPONENT(InventoryController)

void InventoryController::Init(){

	Inventory = InventoryMaker(InventoryNode->getProperty(0)->getParameterPtr(0));
	GUI = InventoryGUI(&Inventory);

	Interact = InventoryInteractor(Unigine::Game::getPlayer(), 1);
}

void InventoryController::Update(){

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_Y)) {
		GUI.Show();
	}

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_U)) {
		GUI.Hide();
	}

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_R)) {
		Unigine::Math::ivec2 Item = Interact.GetItem();
		Inventory.Add(Item);
	}

	Interact.DetectItem();
}

void InventoryController::Shutdown() {
	GUI.Shutdown();
	Interact.Shutdown();
}
