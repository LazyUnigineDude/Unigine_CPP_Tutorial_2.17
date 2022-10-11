#include "SomeClass.h"

REGISTER_COMPONENT(SomeClass)


void SomeClass::Init() {

	
	Unigine::Visualizer::setEnabled(true);
	Unigine::Console::setOnscreen(true);

	Unigine::Log::message("Hi");


}

void SomeClass::Update(){


	Unigine::Visualizer::renderPoint3D(Unigine::Math::vec3_one,0.1f,Unigine::Math::vec4_black);

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_W)) { 
	//	node->setWorldPosition(node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y) * Unigine::Game::getIFps());

		node->setWorldPosition(node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y));
	}
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) {
		node->setWorldPosition(node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_NY) * Unigine::Game::getIFps());
	}
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) {
		node->rotate(Unigine::Math::quat(0,0,-1));
	}
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) { 
		node->rotate(Unigine::Math::quat(0, 0, 1)); }


	if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_LEFT)) { Unigine::Log::message("LMK Pressed"); }



}
