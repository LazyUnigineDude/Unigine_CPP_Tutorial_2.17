#pragma once
#include <Unigine.h>
#include <memory>
#include "PathMaker.h"
#include "HealthBar.h"
#include "Bullet.h"

class ShooterAI : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(ShooterAI, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(Node, MainCharacter)
		PROP_PARAM(Node, PathMakerNode)
		PROP_PARAM(File, BulletPrefab)
		PROP_PARAM(Node, PhysicalTriggerNode)
	
	enum CurrentState{IDLE, ALERT, SEARCH, AGGRESSIVE, SHOOT, DODGE};
	void ChangeState(CurrentState NEW_STATE) { if (STATE != NEW_STATE) { STATE = NEW_STATE; } }

protected:
	
	void Init();
	void Update();

private:
	void GetObjectEnteredInArea(Unigine::BodyPtr Body);
	void AiState();
	void RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed);
	void MoveTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, int Speed);
	CurrentState STATE  = CurrentState::DODGE;
	float Weight = 0, DistanceFactor = 1, CurrentTime = 0;
	int FieldDistance = 30, CurrentHealth;
	void Shoot();

	Unigine::PhysicalTriggerPtr DodgeArea;
	HealthBar* Health;
	PathMaker* Path;
	Bullet* BulletPtr;

	bool isVisible = false;
	Unigine::Math::BoundFrustum BFrustum;
};