#include "MenuWithLoad.h"
REGISTER_COMPONENT(MenuWithLoad)

void MenuWithLoad::Init() {

	GUI = Unigine::Gui::getCurrent();
	Save = new SaveManager(node);

	NewGameButton = Unigine::WidgetButton::create("New Game");
	NewGameButton->setWidth(150);
	NewGameButton->setPosition(80, 10);

	LoadGameButton1 = Unigine::WidgetButton::create("Load AutoSave");
	LoadGameButton1->setWidth(150);
	LoadGameButton1->setPosition(80, 30);

	LoadGameButton2 = Unigine::WidgetButton::create("Load 1");
	LoadGameButton2->setWidth(150);
	LoadGameButton2->setPosition(80, 50);

	LoadGameButton3 = Unigine::WidgetButton::create("Load 2");
	LoadGameButton3->setWidth(150);
	LoadGameButton3->setPosition(80, 70);

	QuitButton = Unigine::WidgetButton::create("Quit");
	QuitButton->setWidth(150);
	QuitButton->setPosition(80, 90);

	NewGameButton->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::OnNew));
	QuitButton->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::OnQuit));

	if (Save->FileExist(Save->AUTOSAVE))	LoadGameButton1->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::OnLoad, SaveManager::AUTOSAVE));
	else									LoadGameButton1->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::Warning));

	if (Save->FileExist(Save->SAVE1))	LoadGameButton2->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::OnLoad, SaveManager::SAVE1));
	else								LoadGameButton2->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::Warning));

	if (Save->FileExist(Save->SAVE2))	LoadGameButton3->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::OnLoad, SaveManager::SAVE2));
	else								LoadGameButton3->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MenuWithLoad::Warning));


	GUI->addChild(NewGameButton, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	GUI->addChild(LoadGameButton1, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	GUI->addChild(LoadGameButton2, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	GUI->addChild(LoadGameButton3, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	GUI->addChild(QuitButton, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
}

void MenuWithLoad::Shutdown() {

	GUI = Unigine::Gui::getCurrent();
	Save->~SaveManager();

	if (GUI->isChild(NewGameButton)) { GUI->removeChild(NewGameButton); NewGameButton->deleteLater(); }
	if (GUI->isChild(LoadGameButton1)) { GUI->removeChild(LoadGameButton1); LoadGameButton1->deleteLater(); }
	if (GUI->isChild(LoadGameButton2)) { GUI->removeChild(LoadGameButton2); LoadGameButton2->deleteLater(); }
	if (GUI->isChild(LoadGameButton3)) { GUI->removeChild(LoadGameButton3); LoadGameButton3->deleteLater(); }
	if (GUI->isChild(QuitButton)) { GUI->removeChild(QuitButton); QuitButton->deleteLater(); }

}

void MenuWithLoad::OnNew() { Unigine::World::loadWorld("NewGame.world"); }
void MenuWithLoad::OnLoad(SaveManager::DATA Data) { Save->Load(Data); }
void MenuWithLoad::OnQuit() { Unigine::Engine::get()->quit(); }
void MenuWithLoad::Warning() { Unigine::Log::error("Does Not Exist\n"); }