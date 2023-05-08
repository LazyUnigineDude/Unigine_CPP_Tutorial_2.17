#pragma once
#include <Unigine.h>;

class MainMenu : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(MainMenu, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(File, WorldChanger)
protected:
	void Init();
	void Update();
};

