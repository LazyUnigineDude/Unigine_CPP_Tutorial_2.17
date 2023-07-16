#pragma once
#include <Unigine.h>
#include "ShooterAnim.h"
#include "PhysicsController.h"
#include "HealthBar.h"
#include "InventoryController.h"


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

protected:
	void Init();
	void Update();
	void UpdatePhysics();
	void ShutDown();

private:
	bool OpenUI = 0;
	void ShowInventory(bool isOpen);
	ShooterAnim* Animation;
	PhysicsController* Physics;
	HealthBar* Health;
	InventoryController* Inventory;
};
