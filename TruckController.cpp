#include "TruckController.h"
REGISTER_COMPONENT(TruckController)


void TruckController::Init() {

	wheelL = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeL->getObjectBody()->getJoint(0));
	wheelR = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeR->getObjectBody()->getJoint(0));
	Joint = Unigine::static_ptr_cast<Unigine::JointBall>(JointNode->getObjectBody()->getJoint(6));
	for (int i = 0; i < TireNodeBack.size(); i++)
		wheelBack[i] = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeBack[i]->getObjectBody()->getJoint(0));
	Truck = JointNode->getObjectBodyRigid();
}

void TruckController::Update() {

	Unigine::Log::message("Speed: %0.2f    tSpeed: %0.2f   tTorque: %0.2f\n", GetSpeed(Truck->getLinearVelocity()), currVel, currTor);
	float iFps = Unigine::Game::getIFps();
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) {

		currVel = Unigine::Math::clamp(currVel + (iFps * Acceleration), currVel, MaxVelocity);
		if (!isBreaking) currTor = Unigine::Math::clamp(currTor + (iFps * Acceleration), currTor, MaxTorque);
	}

	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) {

		currVel = Unigine::Math::clamp(currVel - (iFps * Acceleration), -MaxVelocity, currVel);
		if (!isBreaking) currTor = Unigine::Math::clamp(currTor + (iFps * Acceleration), currTor, MaxTorque);
	}

	else {
		if (currVel < 0) currVel = Unigine::Math::clamp(currVel + (iFps * Acceleration), currVel, 0.0f);
		else currVel = Unigine::Math::clamp(currVel - (iFps * Acceleration), 0.0f, currVel);
		if (!isBreaking) currTor = Unigine::Math::clamp(currTor - (iFps * Acceleration), 0.0f, MaxTorque);
	}

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) currAngle = Unigine::Math::clamp(currAngle + iFps, -0.4f, 0.4f);
	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) currAngle = Unigine::Math::clamp(currAngle - iFps, -0.4f, 0.4f);
	else currAngle = Unigine::Math::lerp(currAngle, 0.0f, iFps * 2);

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_SPACE)) {
		isBreaking = true;
		currTor = Unigine::Math::clamp(currTor - (iFps * BreakingValue), 0.0f, currTor);
		currVel = Unigine::Math::clamp(currVel - (iFps * BreakingValue), 0.0f, currVel);
	}
	else isBreaking = false;

	wheelL->setAxis10(Unigine::Math::vec3(1, currAngle, 0));
	wheelR->setAxis10(Unigine::Math::vec3(1, currAngle, 0));

}

void TruckController::UpdatePhysics() {

	wheelL->setAngularVelocity(currVel);
	wheelR->setAngularVelocity(currVel);
	for (auto& i : wheelBack) i->setAngularVelocity(currVel);

	wheelL->setAngularTorque(currTor * 4);
	wheelR->setAngularTorque(currTor * 4);
	for (auto& i : wheelBack) i->setAngularTorque(currTor);
}
