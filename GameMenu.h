#pragma once
#include <Unigine.h>
#include "SaveManager.h"

class GameMenu : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(GameMenu, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_SHUTDOWN(Shutdown)
		PROP_PARAM(Toggle, NewGame)

protected:
	void Init(), Shutdown();

private:
	Unigine::GuiPtr GUI;
	Unigine::WidgetButtonPtr NewGameButton, SaveGameButton1, SaveGameButton2, SaveGameButton3, QuitButton;

	void OnMainMenu(), OnSave(SaveManager::DATA Data), OnQuit();
	SaveManager* Save;
};
