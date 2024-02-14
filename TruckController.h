#pragma once
#include <Unigine.h>

class TruckController : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(TruckController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		COMPONENT_UPDATE_PHYSICS(UpdatePhysics)
		PROP_PARAM(Node, TireNodeL)
		PROP_PARAM(Node, TireNodeR)
		PROP_ARRAY(Node, TireNodeBack)
		PROP_PARAM(Node, JointNode)

	PROP_PARAM(Float, Acceleration, 5);
	PROP_PARAM(Float, BreakingValue, 10);
	PROP_PARAM(Float, MaxTorque, 100);
	PROP_PARAM(Float, MaxVelocity, 50);

protected:

	void Init();
	void Update();
	void UpdatePhysics();

private:

	Unigine::JointWheelPtr wheelL, wheelR, wheelBack[4];
	Unigine::JointBallPtr Joint;
	Unigine::BodyRigidPtr Truck;
	bool isBreaking{ false };

	float currVel{ 0 }, currTor{ 0 }, currAngle{ 0 }, maxAngle{ 0.4 }, brakeSpeed{ 0.125 };
	const float GetSpeed(const Unigine::Math::vec3& Speed) {

		float speed = Unigine::Math::pow2(Speed.x) + Unigine::Math::pow2(Speed.y) + Unigine::Math::pow2(Speed.z);
		return Unigine::Math::sqrtFast(speed);
	}
};

#pragma once
