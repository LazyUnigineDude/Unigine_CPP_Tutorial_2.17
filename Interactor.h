#pragma once
#include "InventoryMaker.h"
#include "DatabaseController.h"
#include "DoorOpener.h"
#include <string>

struct Interactor : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(Interactor, ComponentBase)
		PROP_PARAM(Mask, MaskNum)

	void Init(Unigine::PlayerPtr Camera);
	bool Update();
	Unigine::Math::ivec2 GetItemFromDetection();
	void Shutdown();

private:
	Unigine::PlayerPtr Camera;
	Unigine::WidgetLabelPtr Label;
	Unigine::WorldIntersectionPtr Intersection;
	Unigine::ObjectPtr Item;
	Unigine::Math::ivec2 _item;
	Unigine::GuiPtr GUI;
	DatabaseController::ITEM_TYPE Type;
};
