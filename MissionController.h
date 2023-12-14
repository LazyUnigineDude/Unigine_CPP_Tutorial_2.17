#pragma once
#include <Unigine.h>
#include "TurretClass.h"
#include "CharacterController.h"
#include "MainMenu.h"

struct MissionController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(MissionController, ComponentBase)
		COMPONENT_INIT(Init, 1)
		COMPONENT_UPDATE(Update, 1)
		COMPONENT_SHUTDOWN(Shutdown)
		PROP_ARRAY(Node, TurretNodes)
		PROP_PARAM(Node, CharacterNode)
		PROP_PARAM(Node, MainMenuNode)

		MissionController* GetMainController() { return getComponent<MissionController>(Unigine::World::getNodeByID(MainNode())); }
	void AddToController(TurretClass* Item) { Turrets.push_back(Item); }

protected:
	void Init();
	void Update();
	void Shutdown();

private:
	int Amount, TotalAmount;
	bool isPaused = 0;
	const int MainNode() { return 1735930620; }
	Unigine::Vector<TurretClass*> Turrets;
	Unigine::WidgetLabelPtr Label;
	CharacterController* Character;
	MainMenu* Menu;
};