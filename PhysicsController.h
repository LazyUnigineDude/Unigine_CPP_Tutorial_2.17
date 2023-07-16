#pragma once

#include <Unigine.h>


class PhysicsController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(PhysicsController, ComponentBase)
		PROP_PARAM(Float, Max_Speed, 10)
		PROP_PARAM(Vec4, FBLR_Speed)
		enum DIRECTIONS{ FORWARD, REVERSE, LEFT, RIGHT };

		double getSpeed();
	void Init(Unigine::NodePtr RigidNode);
	void Move(DIRECTIONS Direction);
	void Run(bool isRunning);
	void AutoRotate(Unigine::PlayerPtr Camera);

private:

	Unigine::BodyRigidPtr MainCharacter;
	Unigine::NodePtr RigidNode;
};
