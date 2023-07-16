#pragma once
#include "InventoryGUI.h"
#include "InventoryInteractor.h"

class InventoryController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(InventoryController, ComponentBase)
		PROP_PARAM(Node ,InventoryNode)
	void Init(Unigine::PlayerPtr Camera, Unigine::NodePtr DropPoint);
	void Show();
	void Hide();
	void Update();
	void Interact();
	void Shutdown();

private:
	Unigine::PropertyParameterPtr Parameter;
	InventoryMaker Inventory;
	InventoryGUI GUI;
	InventoryInteractor Interaction;
};
