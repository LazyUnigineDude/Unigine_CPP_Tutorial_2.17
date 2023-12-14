#pragma once
#include <Unigine.h>;

class MainMenu : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(MainMenu, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		COMPONENT_SHUTDOWN(ShutDown)
		PROP_PARAM(Toggle, isMainMenu)
		PROP_PARAM(String, WorldChangerName)
		PROP_PARAM(File, WorldChanger)

		void MenuOpened(bool isOpen);

protected:
	void Init();
	void Update();
	void ShutDown();

private:
	void onClicked();
	void onQuit();
	bool isPaused;
	Unigine::WidgetButtonPtr Button, QuitButton;
	Unigine::WidgetLabelPtr Description;
	Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();
};

