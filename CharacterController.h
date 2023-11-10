#pragma once
#include <Unigine.h>
#include "ShooterAnim.h"
#include "PhysicsController.h"
#include "HealthBar.h"
#include "InventoryController.h"
#include "Interactor.h"
#include "GunHandler.h"
#include "HUDMaker.h"
#include "SoundController.h"

class CharacterController : public Unigine::ComponentBase {
public:
	COMPONENT_DEFINE(CharacterController,ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		COMPONENT_UPDATE_PHYSICS(UpdatePhysics)
		COMPONENT_SHUTDOWN(ShutDown)
		PROP_PARAM(Node, AnimationNode)
		PROP_PARAM(Node, PhysicsNode)
		PROP_PARAM(Node, HealthBarNode)
		PROP_PARAM(Node, InventoryNode)
		PROP_PARAM(Node, DetectionNode)
		PROP_PARAM(Node, GunNode)
		PROP_PARAM(Node, SoundControllerNode)

protected:
	void Init();
	void Update();
	void UpdatePhysics();
	void ShutDown();

private:
	bool OpenUI = 0;
	void ShowInventory(bool isOpen);
	void ChangeState(ShooterAnim::SHOOTER_STATE State);
	ShooterAnim* Animation;
	PhysicsController* Physics;
	HealthBar* Health;
	InventoryController* Inventory;
	Interactor* Interact;
	GunHandler* Gun;
	HUDMaker* HUD;
	SoundController* Sound;
};
