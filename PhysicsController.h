#pragma once

#include <Unigine.h>


class PhysicsController : public Unigine::ComponentBase
{ 

public:
	COMPONENT_DEFINE(PhysicsController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE_PHYSICS(UpdatePhysics)

		PROP_PARAM(Float, Max_Speed, 10)
		PROP_PARAM(Vec4, FBLR_Speed)

protected:

	void Init();
	void UpdatePhysics();


private:

	float Mass;
	Unigine::BodyRigidPtr MainCharacter;
	void AutoRotate();
};
