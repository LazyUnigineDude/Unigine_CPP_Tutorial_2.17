#pragma once
#include <Unigine.h>

class SomeClass : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(SomeClass, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)
	COMPONENT_UPDATE_PHYSICS(UpdatePhysics)
		PROP_PARAM(Node, TireNodeL)
		PROP_PARAM(Node, TireNodeR)
		PROP_ARRAY(Node, TireNodeBack)
		PROP_PARAM(Node, JointNode)

	PROP_PARAM(Float, acceleration, 250.0f);
	PROP_PARAM(Float, default_torque, 75.0);

protected:

	void Init();
	void Update();
	void UpdatePhysics();

private:

	Unigine::JointWheelPtr wheelL, wheelR, wheelLB, wheelRB;
	Unigine::JointBallPtr Joint;

	float currVel{ 0 }, currTorque{ 0 }, currAngle{ 0 }, maxAngle{ 30 };
};

