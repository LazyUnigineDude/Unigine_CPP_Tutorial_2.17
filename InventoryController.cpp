#include "InventoryController.h"
REGISTER_COMPONENT(InventoryController)

void InventoryController::Init(Unigine::PlayerPtr Camera, Unigine::NodePtr DropPoint){

	Inventory = InventoryMaker(InventoryNode->getProperty(0)->getParameterPtr(0));
	GUI = InventoryGUI(&Inventory, DropPoint);
}

void InventoryController::Show() { GUI.Show(); }
void InventoryController::Hide() { GUI.Hide(); }
void InventoryController::AddToInventory(Unigine::Math::ivec2 Item) { Inventory.Add(Item); }

void InventoryController::Shutdown() {
	GUI.Shutdown();
}
