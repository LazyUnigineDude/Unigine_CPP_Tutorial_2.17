#include "PhysicsController.h"

REGISTER_COMPONENT(PhysicsController)

void PhysicsController::Init() {

	MainCharacter = node->getObjectBodyRigid();
	MainCharacter->setMaxLinearVelocity(Max_Speed.get() * 2);
}

void PhysicsController::UpdatePhysics() {


	AutoRotate();

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_Y) * 10);
	}


	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NY) * 6);
	}


	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_X) * 8);
	}


	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A))
	{
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NX) * 8);
	}

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT)) { MainCharacter->setLinearVelocity(MainCharacter->getLinearVelocity() * 1.08f); }
}

void PhysicsController::AutoRotate() {

	Unigine::Math::vec3 CameraView, PlayerView;

	CameraView = Unigine::Game::getPlayer()->getWorldDirection();
	PlayerView = node->getWorldDirection(Unigine::Math::AXIS_Y);

	float Angle = Unigine::Math::getAngle(CameraView, PlayerView, node->getWorldDirection(Unigine::Math::AXIS_Z));

	MainCharacter->addAngularImpulse(node->getWorldDirection() * Angle);
}