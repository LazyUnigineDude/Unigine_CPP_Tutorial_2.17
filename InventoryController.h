#pragma once
#include "InventoryGUI.h"

class InventoryController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(InventoryController, ComponentBase)
		PROP_PARAM(Node ,InventoryNode)
	void Init(Unigine::PlayerPtr Camera, Unigine::NodePtr DropPoint);
	void Show();
	void Hide();
	void AddToInventory(Unigine::Math::ivec2 Item);
	void Shutdown();

private:
	Unigine::PropertyParameterPtr Parameter;
	InventoryMaker Inventory;
	InventoryGUI GUI;
};
