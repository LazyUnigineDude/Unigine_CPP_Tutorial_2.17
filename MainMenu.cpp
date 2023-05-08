#include "MainMenu.h"
REGISTER_COMPONENT(MainMenu)

void MainMenu::Init() {}

void MainMenu::Update() {

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_EQUALS)) { Unigine::World::loadWorld(WorldChanger); }
}
