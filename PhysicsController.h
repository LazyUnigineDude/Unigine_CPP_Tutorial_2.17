#pragma once

#include <Unigine.h>


class PhysicsController : public Unigine::ComponentBase
{ 

public:
	COMPONENT_DEFINE(PhysicsController,ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE_PHYSICS(UpdatePhysics)
	
	PROP_PARAM(Float, Max_Speed, 15)

protected:

	void Init();
	void UpdatePhysics();


private:

	Unigine::BodyRigidPtr MainCharacter;
	void AutoRotate();
};
