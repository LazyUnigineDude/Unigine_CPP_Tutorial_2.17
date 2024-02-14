#include "SomeClass.h"

REGISTER_COMPONENT(SomeClass)


void SomeClass::Init() {

	wheelL  = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeL->getObjectBody()->getJoint(0));
	wheelR  = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeR->getObjectBody()->getJoint(0));
	Joint   = Unigine::static_ptr_cast<Unigine::JointBall>(JointNode->getObjectBody()->getJoint(4));
	wheelLB = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeBack[0]->getObjectBody()->getJoint(0));
	wheelRB = Unigine::static_ptr_cast<Unigine::JointWheel>(TireNodeBack[1]->getObjectBody()->getJoint(0));
}

void SomeClass::Update() {

	float iFps = Unigine::Game::getIFps();
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) {

		currTorque = default_torque;
		currVel = Unigine::Math::max(currVel, 0.0f);
		currVel += iFps * acceleration * 10;
	}

	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) {

		currTorque = default_torque;
		currVel = Unigine::Math::min(currVel, 0.0f);
		currVel -= iFps * acceleration;
	}

	else { currVel *= Unigine::Math::exp(-iFps); currTorque *= Unigine::Math::exp(-iFps); }

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) currAngle = Unigine::Math::clamp(currAngle + iFps, -0.4f, 0.4f);
	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) currAngle = Unigine::Math::clamp(currAngle - iFps, -0.4f, 0.4f);
	else currAngle = Unigine::Math::lerp(currAngle, 0.0f, iFps * 2); 

	//if (currAngle == 0.0f) Joint->setAngularSpring(150);
	//else Joint->setAngularSpring(0);

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_SPACE)) {
		wheelL->setLinearDamping(100);
		wheelR->setLinearDamping(100);
	}
	else {
		wheelL->setLinearDamping(1);
		wheelR->setLinearDamping(1);
	}

	wheelL->setAxis10(Unigine::Math::vec3(1, currAngle, 0));
	wheelR->setAxis10(Unigine::Math::vec3(1, currAngle, 0));

}

void SomeClass::UpdatePhysics() {

	wheelL->setAngularVelocity(currVel * 2);
	wheelR->setAngularVelocity(currVel * 2);	
	wheelLB->setAngularVelocity(currVel);
	wheelRB->setAngularVelocity(currVel);

	wheelL->setAngularTorque(currTorque * 2);
	wheelR->setAngularTorque(currTorque * 2);
	wheelLB->setAngularTorque(currTorque);
	wheelRB->setAngularTorque(currTorque);
}
