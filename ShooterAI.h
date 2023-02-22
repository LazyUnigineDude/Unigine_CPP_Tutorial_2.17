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
		PROP_PARAM(File, BulletPrefab)
		PROP_PARAM(Node, PhysicalTriggerNode)
	
	enum CurrentState{IDLE, ALERT, SEARCH, AGGRESSIVE, SHOOT, DODGE};
	void ChangeState(CurrentState NEW_STATE) { if (STATE != NEW_STATE) { STATE = NEW_STATE; } }

	void StartAI();
	void Init(float Duration, std::vector<Unigine::Math::Vec3> PathLines, Unigine::NodePtr MainCharacter);
	void Update();

private:

	CurrentState STATE  = CurrentState::IDLE;
	Unigine::NodePtr MainCharacter;

	float 
		Weight = 0, 
		DistanceFactor = 1, 
		CurrentTime = 0;
	int CurrentHealth, 
		const MASK_PRIMARY = 1,
		const MASK_SECONDARY = 2, 
		const FIELD_DISTANCE = 30, 
		const DAMAGE = 1;
	bool isVisible, CanMove = 0;

	void Shoot();
	void AiState();

	HealthBar* Health;
	DetectionMaker Detector;
	PathMaker MainPath;
	AIGunHandler GunHandler;
};