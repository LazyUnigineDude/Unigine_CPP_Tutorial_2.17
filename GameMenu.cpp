#include "GameMenu.h"
REGISTER_COMPONENT(GameMenu)

void GameMenu::Init() {

	GUI = Unigine::Gui::getCurrent();
	Save = new SaveManager(node);

	NewGameButton = Unigine::WidgetButton::create("Main Menu");
	NewGameButton->setWidth(150);
	NewGameButton->setPosition(150, 10);
	NewGameButton->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &GameMenu::OnMainMenu));
	GUI->addChild(NewGameButton, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);

	SaveGameButton1 = Unigine::WidgetButton::create("AutoSave");
	SaveGameButton1->setWidth(150);
	SaveGameButton1->setPosition(150, 30);
	SaveGameButton1->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &GameMenu::OnSave, SaveManager::AUTOSAVE));
	GUI->addChild(SaveGameButton1, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);

	SaveGameButton2 = Unigine::WidgetButton::create("Save 1");
	SaveGameButton2->setWidth(150);
	SaveGameButton2->setPosition(150, 50);
	SaveGameButton2->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &GameMenu::OnSave, SaveManager::SAVE1));
	GUI->addChild(SaveGameButton2, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);

	SaveGameButton3 = Unigine::WidgetButton::create("Save 2");
	SaveGameButton3->setWidth(150);
	SaveGameButton3->setPosition(150, 70);
	SaveGameButton3->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &GameMenu::OnSave, SaveManager::SAVE2));
	GUI->addChild(SaveGameButton3, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);

	QuitButton = Unigine::WidgetButton::create("Quit");
	QuitButton->setWidth(150);
	QuitButton->setPosition(150, 90);
	QuitButton->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &GameMenu::OnQuit));
	GUI->addChild(QuitButton, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);

	if (!NewGame) Save->LoadObjectsIntoWorld();
}

void GameMenu::Shutdown() {

	GUI = Unigine::Gui::getCurrent();

	if (GUI->isChild(NewGameButton)) { GUI->removeChild(NewGameButton); NewGameButton->deleteLater(); }
	if (GUI->isChild(SaveGameButton1)) { GUI->removeChild(SaveGameButton1); SaveGameButton1->deleteLater(); }
	if (GUI->isChild(SaveGameButton2)) { GUI->removeChild(SaveGameButton2); SaveGameButton2->deleteLater(); }
	if (GUI->isChild(SaveGameButton3)) { GUI->removeChild(SaveGameButton3); SaveGameButton3->deleteLater(); }
	if (GUI->isChild(QuitButton)) { GUI->removeChild(QuitButton); QuitButton->deleteLater(); }
	OnSave(Save->AUTOSAVE); // Autosave Feature;
}

void GameMenu::OnMainMenu() { Unigine::World::loadWorld("CPP_Check.world"); }
void GameMenu::OnQuit() { Unigine::Engine::get()->quit(); }

void GameMenu::OnSave(SaveManager::DATA Data) { Save->Save(Data); }
