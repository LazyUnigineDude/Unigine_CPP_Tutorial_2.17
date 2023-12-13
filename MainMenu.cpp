#include "MainMenu.h"
REGISTER_COMPONENT(MainMenu)

void MainMenu::Init() {

	GUI = Unigine::Gui::getCurrent();

	Button = Unigine::WidgetButton::create();
	Button->setText(WorldChangerName);
	Button->setFontSize(50);
	Button->setWidth(200);
	Button->setFontColor(Unigine::Math::vec4_white);
	Button->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MainMenu::onClicked));
	Button->setPosition((GUI->getWidth() * 0.5) - 100, (GUI->getHeight() * 0.5) - 50);

	QuitButton = Unigine::WidgetButton::create();
	QuitButton->setText("Quit");
	QuitButton->setFontSize(50);
	QuitButton->setWidth(200);
	QuitButton->setFontColor(Unigine::Math::vec4_white);
	QuitButton->setButtonColor(Unigine::Math::vec4(0.6,0.3,0.3,0.8));
	QuitButton->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &MainMenu::onQuit));
	QuitButton->setPosition((GUI->getWidth() * 0.5) - 100, (GUI->getHeight() * 0.5) + 50);

	MenuOpened(isMainMenu);
}

void MainMenu::Update() {

	if (!isMainMenu) {
		// key escape open close menu
		if (Unigine::Input::isKeyDown(Unigine::Input::KEY_ESC))
		{
			isPaused = (isPaused) ? 0 : 1;
			MenuOpened(isPaused);
		}
	}
}

void MainMenu::MenuOpened(bool isOpened) {
	GUI = Unigine::Gui::getCurrent();
	if (isOpened) {
		if (!GUI->isChild(Button))      GUI->addChild(Button,		GUI->ALIGN_OVERLAP | GUI->ALIGN_EXPAND);
		if (!GUI->isChild(QuitButton))  GUI->addChild(QuitButton,	GUI->ALIGN_OVERLAP | GUI->ALIGN_EXPAND);
	}
	else {
		if (GUI->isChild(Button))		GUI->removeChild(Button);
		if (GUI->isChild(QuitButton))	GUI->removeChild(QuitButton);
	}
}

void MainMenu::ShutDown() { MenuOpened(false); Button->deleteLater(); QuitButton->deleteLater(); }
void MainMenu::onClicked() { Unigine::World::loadWorld(WorldChanger); }
void MainMenu::onQuit() { Unigine::Engine::get()->quit(); }
