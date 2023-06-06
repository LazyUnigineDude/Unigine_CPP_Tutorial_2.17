#pragma once
#include <Unigine.h>

class InventoryController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(InventoryController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)

protected:
	void Init();
	void Update();

private:

};

