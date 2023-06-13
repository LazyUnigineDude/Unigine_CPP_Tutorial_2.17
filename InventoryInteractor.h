#pragma once
#include "InventoryMaker.h"

struct InventoryInteractor {

public:
	InventoryInteractor() = default;
	InventoryInteractor(Unigine::PlayerPtr Camera);
	bool GotItemWithID();
	Unigine::ObjectPtr GetItem();

private:
	Unigine::ObjectPtr Item;
	Unigine::PlayerPtr Camera
};

inline InventoryInteractor::InventoryInteractor(Unigine::PlayerPtr Camera) { this->Camera = Camera; }
Unigine::ObjectPtr InventoryInteractor::GetItem() { return Item; }

bool InventoryInteractor::GotItemWithID() {

	return 0;
}

