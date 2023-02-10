#pragma once
#include <Unigine.h>
#include "HealthBar.h"
#include "PhysicsController.h"
#include "PathMaker.h"
#include "NavigationMaker.h"
#include "AIComponents.h"

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

	CurrentState STATE  = CurrentState::IDLE;

	float 
		Weight = 0, 
		DistanceFactor = 1, 
		CurrentTime = 0;
	int CurrentHealth, 
		const MASK_PRIMARY = 1,
		const MASK_SECONDARY = 2, 
		const FIELD_DISTANCE = 30, 
		const DAMAGE = 1;
	bool isVisible;

	void Shoot();
	void AiState();

	HealthBar* Health;
	NavigationMaker* MainNav;
	PathMaker MainPath;
	DetectionMaker Detector;
	AIGunHandler GunHandler;
};