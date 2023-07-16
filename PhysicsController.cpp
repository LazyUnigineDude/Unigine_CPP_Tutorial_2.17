	#include "PhysicsController.h"

REGISTER_COMPONENT(PhysicsController)

void PhysicsController::Init(Unigine::NodePtr RigidNode) {

	MainCharacter = RigidNode->getObjectBodyRigid();
}

void PhysicsController::Move(DIRECTIONS Direction) {

	switch (Direction) {
	case PhysicsController::FORWARD:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_Y) * FBLR_Speed.get().x * 20);
		break;
	case PhysicsController::REVERSE:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NY) * FBLR_Speed.get().y * 20);
		break;
	case PhysicsController::LEFT:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NX) * FBLR_Speed.get().w * 20);
		break;
	case PhysicsController::RIGHT:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_X) * FBLR_Speed.get().z * 20);
		break;
	default:
		break;
	}

	}

void PhysicsController::UpdatePhysics() {

	AutoRotate();

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

double PhysicsController::getSpeed() {

	double speed = Unigine::Math::pow2(MainCharacter->getLinearVelocity().x) + Unigine::Math::pow2(MainCharacter->getLinearVelocity().y) + Unigine::Math::pow2(MainCharacter->getLinearVelocity().z);
	speed = Unigine::Math::sqrtFast(speed);
	return speed;
}