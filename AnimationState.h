#pragma once

#include <Unigine.h>

class AnimationState : public Unigine::ComponentBase
{

public:

	COMPONENT_DEFINE(AnimationState, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)


	PROP_PARAM(File, IdleAnim)
	PROP_PARAM(File, WalkAnim)
	PROP_PARAM(File, R_WalkAnim)
	PROP_PARAM(File, RunAnim)

protected:
	void Init();
	void Update();


private:

	Unigine::ObjectMeshSkinnedPtr MainCharacter;
	float Weight = 0;
	bool isWeightChanged = false;


	enum ANIMSTATES {PROCEDURAL = 0, IDLE, WALK, REVERSE_WALK, RUN, COUNT};
	ANIMSTATES MainState = ANIMSTATES::IDLE, PrevState = ANIMSTATES::IDLE;
	void ChangeState();
	void ResetWeight();

};

