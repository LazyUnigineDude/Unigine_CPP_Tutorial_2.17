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
		PROP_PARAM(Node, NavigationNode)
		PROP_PARAM(Node, ObstacleNode)
	
	enum CurrentState{IDLE, ALERT, SEARCH, AGGRESSIVE, SHOOT, DODGE};
	void ChangeState(CurrentState NEW_STATE) { if (STATE != NEW_STATE) { STATE = NEW_STATE; } }

protected:
	
	void Init();
	void Update();

private:
	void NavMeshCheck();
	void GetObjectEnteredInArea(Unigine::BodyPtr Body);
	void AiState();
	void RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed);
	void MoveTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, int Speed);
	CurrentState STATE  = CurrentState::IDLE;
	float Weight = 0, DistanceFactor = 1, CurrentTime = 0;
	int FieldDistance = 30, CurrentHealth;
	void Shoot();

	Unigine::PhysicalTriggerPtr DodgeArea;
	HealthBar* Health;
	PathMaker* Path, *ObjPath;
	Bullet* BulletPtr;

	Unigine::NavigationMeshPtr NavMesh;
	Unigine::PathRoutePtr Pathing1, Pathing2, Pathing3, Pathing4;
	Unigine::Math::Vec3 PathPoints1, PathPoints2, PathPoints3, PathPoints4;
	Unigine::ObstacleBoxPtr ObstaclePtr;

	bool isVisible = false;
	Unigine::Math::BoundFrustum BFrustum;
};