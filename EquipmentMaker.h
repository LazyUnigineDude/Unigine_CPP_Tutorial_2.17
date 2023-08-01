#pragma once
#include "InventoryMaker.h"
#include <Unigine.h>

struct EquipmentMaker : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(EquipmentMaker, ComponentBase)
		PROP_PARAM(Node, EquipmentNode)

	void Init();
	InventoryMaker* GetEquipment() { return &Equipment; }

private:
	InventoryMaker Equipment;
	Unigine::PropertyParameterPtr Parameter;
};