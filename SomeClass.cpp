#include "SomeClass.h"

REGISTER_COMPONENT(SomeClass)


void SomeClass::Init() {

	Unigine::Visualizer::setEnabled(true);
	Unigine::Console::setOnscreen(true);

	Unigine::EngineWindowPtr Windows = Unigine::WindowManager::getMainWindow();
	Windows->setSize(Unigine::Math::ivec2(1600,900));
	Windows->setPosition(Unigine::Math::ivec2(400,50));

	Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();

	Button = Unigine::WidgetButton::create();
	Button->setButtonColor(Unigine::Math::vec4_white);
	Button->setFontColor(Unigine::Math::vec4_black);
	Button->setFontSize(20);
	Button->setWidth(100);
	Button->setHeight(100);
	Button->setToggleable(true);
	Button->setPosition(750,400);
	Button->setText("OFF");

	Button->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &SomeClass::CheckStatus));

	GUI->addChild(Button, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
}

void SomeClass::Update(){


	//Unigine::Visualizer::renderPoint3D(Unigine::Math::Vec3_one,0.1f,Unigine::Math::vec4_black);

	//if (Unigine::Input::isKeyDown(Unigine::Input::KEY_W)) { 
	////	node->setWorldPosition(node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y) * Unigine::Game::getIFps());

	//	node->setWorldPosition(node->getWorldPosition() + Unigine::Math::Vec3(node->getWorldDirection(Unigine::Math::AXIS_Y)));
	//}
	//if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) {
	//	node->setWorldPosition(node->getWorldPosition() + Unigine::Math::Vec3(node->getWorldDirection(Unigine::Math::AXIS_NY)) * Unigine::Game::getIFps());
	//}
	//if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) {
	//	node->rotate(Unigine::Math::quat(0,0,-1));
	//}
	//if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) { 
	//	node->rotate(Unigine::Math::quat(0, 0, 1)); }


	//if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_LEFT)) { Unigine::Log::message("LMK Pressed"); }



}
