#include "SomeClass.h"

REGISTER_COMPONENT(SomeClass)


void SomeClass::Init() {

	//Unigine::Visualizer::setEnabled(true);
	//Unigine::Console::setOnscreen(true);

	//Unigine::EngineWindowPtr Windows = Unigine::WindowManager::getMainWindow();
	//Windows->setSize(Unigine::Math::ivec2(1600,900));
	//Windows->setPosition(Unigine::Math::ivec2(400,50));

	//Unigine::GuiPtr GUI = Unigine::Gui::getCurrent();

	//Button = Unigine::WidgetButton::create();
	//Button->setButtonColor(Unigine::Math::vec4_white);
	//Button->setFontColor(Unigine::Math::vec4_black);
	//Button->setFontSize(20);
	//Button->setWidth(100);
	//Button->setHeight(100);
	//Button->setToggleable(true);
	//Button->setPosition(750,400);
	//Button->setTexture(Image.get());

	//Button->addCallback(GUI->CLICKED, Unigine::MakeCallback(this, &SomeClass::CheckStatus));

	//GUI->addChild(Button, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);

	wheelL = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeL->getObjectBody()->getJoint(0));
	wheelR = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeR->getObjectBody()->getJoint(0));
	Engine = EngineNode->getObjectBodyRigid();
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

	float iFps = Unigine::Game::getIFps();

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) {

		currTorque = default_torque;
		currVel = Unigine::Math::max(currVel, 0.0f);
		currVel += iFps * acceleration;
	}

	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) {

		currTorque = default_torque;
		currVel = Unigine::Math::min(currVel, 0.0f);
		currVel -= iFps * acceleration;
	}

	else currVel *= Unigine::Math::exp(-iFps);

	//if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) currAngle = Unigine::Math::clamp(currAngle + iFps, -0.2f, 0.2f);
	//if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) currAngle = Unigine::Math::clamp(currAngle - iFps, -0.2f, 0.2f);

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) Engine->addAngularImpulse(Unigine::Math::vec3_up);
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) Engine->addAngularImpulse(Unigine::Math::vec3_down);

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_SPACE)) {
		wheelL->setLinearDamping(100);
		wheelR->setLinearDamping(100);
	}
	else {
		wheelL->setLinearDamping(1);
		wheelR->setLinearDamping(1);
	}

	//wheelL->setAxis10(Unigine::Math::vec3(1, currAngle, 0));
	//wheelR->setAxis10(Unigine::Math::vec3(1, currAngle, 0));

}

void SomeClass::UpdatePhysics() {

	wheelL->setAngularVelocity(currVel);
	wheelR->setAngularVelocity(currVel);

	wheelL->setAngularTorque(currTorque);
	wheelR->setAngularTorque(currTorque);
}
