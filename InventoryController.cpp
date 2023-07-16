#include "InventoryController.h"
REGISTER_COMPONENT(InventoryController)

void InventoryController::Init(Unigine::PlayerPtr Camera, Unigine::NodePtr DropPoint){

	Inventory = InventoryMaker(InventoryNode->getProperty(0)->getParameterPtr(0));
	GUI = InventoryGUI(&Inventory, DropPoint);
	Interaction = InventoryInteractor(Camera, 0x00000002);
}

void InventoryController::Show() { GUI.Show(); }
void InventoryController::Hide() { GUI.Hide(); }
void InventoryController::Interact() { Inventory.Add(Interaction.GetItem()); }
void InventoryController::Update(){	Interaction.DetectItem(); }

void InventoryController::Shutdown() {
	GUI.Shutdown();
	Interaction.Shutdown();
}
