#pragma once
#include <Unigine.h>

class SomeClass : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(SomeClass, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)
	COMPONENT_UPDATE_PHYSICS(UpdatePhysics)
		//PROP_PARAM(File, Image)
		PROP_PARAM(Node, EngineNode)
		PROP_PARAM(Node, TireNodeL)
		PROP_PARAM(Node, TireNodeR)

	PROP_PARAM(Float, acceleration, 50.0f);
	PROP_PARAM(Float, max_velocity, 90.0f);
	PROP_PARAM(Float, default_torque, 5.0f);

	PROP_PARAM(Float, turn_speed, 50.0f);

protected:

	void Init();
	void Update();
	void UpdatePhysics();

private:
	Unigine::WidgetButtonPtr Button;
	void x() { Button->setButtonColor(Unigine::Math::vec4_green); }
	void y() { Button->setButtonColor(Unigine::Math::vec4_white); }

	void CheckStatus() { (Button->isToggled()) ?  x() : y() ; }

	Unigine::JointWheelPtr wheelL, wheelR;
	Unigine::BodyRigidPtr Engine;

	float currVel{ 0 }, currTorque{ 0 }, currAngle{ 0 }, maxAngle{ 30 };
};

