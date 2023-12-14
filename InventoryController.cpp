#include "InventoryController.h"
REGISTER_COMPONENT(InventoryController)

void InventoryController::Init(Unigine::PlayerPtr Camera, Unigine::NodePtr DropPoint, HealthBar* Health){

	Inventory = InventoryMaker(InventoryNode->getProperty(0)->getParameterPtr(0));
	GUI = InventoryGUI(&Inventory, DropPoint, Health);
}

void InventoryController::Show() { GUI.Show(); Unigine::Input::setMouseHandle(Unigine::Input::MOUSE_HANDLE_USER); }
void InventoryController::Hide() { GUI.Hide(); Unigine::Input::setMouseHandle(Unigine::Input::MOUSE_HANDLE_GRAB); }
void InventoryController::AddToInventory(Unigine::Math::ivec2 Item) { Inventory.Add(Item); }

void InventoryController::Shutdown() {
	GUI.Shutdown();
}
