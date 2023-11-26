#pragma once
#include <Unigine.h>
#include "SaveManager.h"

class MenuWithLoad : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(MenuWithLoad, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_SHUTDOWN(Shutdown)

protected:
	void Init(), Shutdown();

private:
	Unigine::GuiPtr GUI;
	Unigine::WidgetButtonPtr NewGameButton, LoadGameButton1, LoadGameButton2, LoadGameButton3, QuitButton;

	void OnNew(), OnLoad(SaveManager::DATA Data), OnQuit(), Warning();
	SaveManager* Save;
};