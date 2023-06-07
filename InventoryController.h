#pragma once
#include "InventoryGUI.h"

class InventoryController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(InventoryController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		COMPONENT_SHUTDOWN(Shutdown)
		PROP_PARAM(Node ,InventoryNode)

protected:
	void Init();
	void Update();
	void Shutdown();

private:
	Unigine::PropertyParameterPtr Parameter;
	InventoryMaker Inventory;
	InventoryGUI GUI;
};
