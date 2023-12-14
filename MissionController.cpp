#include "MissionController.h"
REGISTER_COMPONENT(MissionController)

void MissionController::Init() {

	Amount = TurretNodes.size();
	TotalAmount = TurretNodes.size();
	Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();

	std::string S = "Turrets: " + std::to_string(Amount) + " / " + std::to_string(TotalAmount);
	Label = Unigine::WidgetLabel::create(S.c_str());
	Label->setFontSize(32);
	Label->setFontOutline(2);
	Label->setPosition((GUI->getWidth() * 0.5) - 60, 10);
	GUI->addChild(Label, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);;
	Unigine::Input::setMouseHandle(Unigine::Input::MOUSE_HANDLE_GRAB);

	for (int i = 0; i < TurretNodes.size(); i++) { AddToController(getComponent<TurretClass>(TurretNodes[i])); }
	Character = getComponent<CharacterController>(CharacterNode);
	Menu = getComponent<MainMenu>(MainMenuNode);
}

void MissionController::Update() {
	
	if (isPaused) return;
	if (isPaused == 0 && Character->isDead()) {
		std::string S = "You Lost!";
		Label->setText(S.c_str());
		Unigine::Game::setScale(0);
		Menu->MenuOpened(1);
		Unigine::Input::setMouseHandle(Unigine::Input::MOUSE_HANDLE_USER);
		isPaused = 1;
		Unigine::Game::getPlayer()->setListener(0);
		return;
	}

	int x = TotalAmount;
	for (auto& i : Turrets) if (i->isDestroyed()) { x--; }

	if (isPaused == 0 && x == 0) {
		std::string S = "You Won!";
		Label->setText(S.c_str());
		Unigine::Game::setScale(0);
		Menu->MenuOpened(1);
		Unigine::Input::setMouseHandle(Unigine::Input::MOUSE_HANDLE_USER);
		isPaused = 1;
		Unigine::Game::getPlayer()->setListener(0);
		return;
	}

	if (Amount != x) {
		Amount = x;
		std::string S = "Turrets: " + std::to_string(Amount) + " / " + std::to_string(TotalAmount);
		Label->setText(S.c_str());
	}


}

void MissionController::Shutdown() {

	Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();

	if (GUI->isChild(Label)) GUI->removeChild(Label);
	if (Label) Label->deleteLater();
}