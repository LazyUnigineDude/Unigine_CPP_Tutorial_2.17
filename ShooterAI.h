#pragma once
#include <Unigine.h>
#include "PathMaker.h"
#include "HealthBar.h"
#include "Bullet.h"
#include "NavigationMaker.h"

class ShooterAI : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(ShooterAI, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(Node, MainCharacter)
		PROP_PARAM(File, BulletPrefab)
		PROP_PARAM(Node, PhysicalTriggerNode)
		PROP_PARAM(Node, PathFindingNode)
	
	enum CurrentState{IDLE, ALERT, SEARCH, AGGRESSIVE, SHOOT, DODGE};
	void ChangeState(CurrentState NEW_STATE) { if (STATE != NEW_STATE) { STATE = NEW_STATE; } }

protected:

	void Init();
	void Update();

private:
	void GetObjectEnteredInArea(Unigine::BodyPtr Body);
	void AiState();
	CurrentState STATE  = CurrentState::IDLE;
	float Weight = 0, DistanceFactor = 1, CurrentTime = 0;
	int FieldDistance = 30, CurrentHealth;
	void Shoot();

	Unigine::PhysicalTriggerPtr DodgeArea;
	HealthBar* Health;
	PathMaker* MainPath;
	Bullet* BulletPtr;
	NavigationMaker* MainNav;

	bool isVisible = false;
	Unigine::Math::BoundFrustum BFrustum;
};