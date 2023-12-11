	#include "PhysicsController.h"

REGISTER_COMPONENT(PhysicsController)

void PhysicsController::Init(Unigine::NodePtr RigidNode) {

	MainCharacter = RigidNode->getObjectBodyRigid();
	this->RigidNode = RigidNode;
}

void PhysicsController::Move(DIRECTIONS Direction) {

	float CorrectedMass = MainCharacter->getMass() * Unigine::Physics::getIFps();

	switch (Direction) {
	case PhysicsController::FORWARD:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_Y) * FBLR_Speed.get().x * CorrectedMass);
		break;
	case PhysicsController::REVERSE:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NY) * FBLR_Speed.get().y * CorrectedMass);
		break;
	case PhysicsController::LEFT:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_NX) * FBLR_Speed.get().w * CorrectedMass);
		break;
	case PhysicsController::RIGHT:
		MainCharacter->addLinearImpulse(node->getWorldDirection(Unigine::Math::AXIS_X) * FBLR_Speed.get().z * CorrectedMass);
		break;
	default: break; }
}

void PhysicsController::Run(bool isRunning) {

		if (isRunning) MainCharacter->addLinearImpulse(MainCharacter->getLinearVelocity().normalize() * Max_Speed.get());
}

void PhysicsController::AutoRotate(Unigine::PlayerPtr Camera) {

	Unigine::Math::vec3 CameraView, PlayerView;

	CameraView = Camera->getWorldDirection();
	PlayerView = RigidNode->getWorldDirection(Unigine::Math::AXIS_Y);

	float Angle = Unigine::Math::getAngle(CameraView, PlayerView, RigidNode->getWorldDirection(Unigine::Math::AXIS_Z));

	MainCharacter->addAngularImpulse(RigidNode->getWorldDirection() * Angle);
}

double PhysicsController::getSpeed() {

	double speed = Unigine::Math::pow2(MainCharacter->getLinearVelocity().x) + Unigine::Math::pow2(MainCharacter->getLinearVelocity().y) + Unigine::Math::pow2(MainCharacter->getLinearVelocity().z);
	speed = Unigine::Math::sqrtFast(speed);
	return speed;
}