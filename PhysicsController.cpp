#include "PhysicsController.h"

REGISTER_COMPONENT(PhysicsController)

void PhysicsController::Init() {

	MainCharacter = node->getObjectBodyRigid();
	Mass = MainCharacter->getMass();
}

void PhysicsController::UpdatePhysics() {

	AutoRotate();
	Unigine::Log::message("%f %f %f\n", MainCharacter->getLinearVelocity().x, MainCharacter->getLinearVelocity().y, MainCharacter->getLinearVelocity().z);

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_Y) * FBLR_Speed.get().x * 20);
	}


	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NY) * FBLR_Speed.get().y * 20);
	}


	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_X) * FBLR_Speed.get().z * 20);
	}


	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NX) * FBLR_Speed.get().w * 20);
	}

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_LEFT_SHIFT)) {
		MainCharacter->setMaxLinearVelocity(Max_Speed.get() * 1.5f);
	}

	else {
		MainCharacter->setMaxLinearVelocity(Max_Speed.get());
	}
}

void PhysicsController::AutoRotate() {

	Unigine::Math::vec3 CameraView, PlayerView;

	CameraView = Unigine::Game::getPlayer()->getWorldDirection();
	PlayerView = node->getWorldDirection(Unigine::Math::AXIS_Y);

	float Angle = Unigine::Math::getAngle(CameraView, PlayerView, node->getWorldDirection(Unigine::Math::AXIS_Z));

	MainCharacter->addAngularImpulse(node->getWorldDirection() * Angle);
}