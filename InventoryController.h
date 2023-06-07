#pragma once
#include "InventoryMaker.h"

class InventoryController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(InventoryController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(Node ,InventoryNode)

protected:
	void Init();
	void Update();

private:
	Unigine::PropertyParameterPtr Parameter;
	InventoryMaker Inventory;
};
