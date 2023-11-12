#pragma once
#include <Unigine.h>

class ShooterAnim : public Unigine::ComponentBase
{

public:
	COMPONENT_DEFINE(ShooterAnim, ComponentBase)
		PROP_ARRAY(File, ANIM_NORMAL)
		PROP_ARRAY(File, ANIM_EQUIP)
		PROP_ARRAY(File, ANIM_AIM)
		enum SHOOTER_STATE { NORMAL, EQUIPPED, AIMED, _COUNT };
		enum ANIM_STATE { IDLE, WALK, RUN, REVERSE_WALK, SIDEWALK_L, SIDEWALK_R, COUNT };

		void Init(Unigine::NodePtr MeshSkinnedObj);
		void Update(float IFPS, float Time);
		void ChangeState(SHOOTER_STATE STATE);
		void ChangeAnim(ANIM_STATE STATE);
		bool IsIdle();

private:

	Unigine::ObjectMeshSkinnedPtr MainCharacter;
	float Weight = 0;
	bool isWeightChanged = false;

	void UpdateAnims();
	const char* GetAnimation(SHOOTER_STATE S_STATE, ANIM_STATE A_STATE);
	void SetAnimation(SHOOTER_STATE S_STATE, ANIM_STATE A_STATE, int Layer);
	void LerpLayer() { MainCharacter->lerpLayer(0, 0, 1, Weight); }

	SHOOTER_STATE _STATE = SHOOTER_STATE::NORMAL, _PREVSTATE = SHOOTER_STATE::NORMAL;
	ANIM_STATE STATE = ANIM_STATE::IDLE, PREVSTATE = ANIM_STATE::IDLE;
	
	Unigine::ObjectPtr Gun;
	Unigine::NodeReferencePtr BulletPrefab;
	Unigine::Vector<Unigine::NodePtr> ObjectsCaptured;
};

