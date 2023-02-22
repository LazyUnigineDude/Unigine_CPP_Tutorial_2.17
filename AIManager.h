#pragma once
#include "ShooterAI.h"

class AIManager : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(AIManager, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		
		PROP_PARAM(Node, MainCharacter)
		PROP_PARAM(Node, NavigationNode)
		PROP_PARAM(File, AINodePrefab)

protected:
	void Init();
	void Update();

private:
	NavigationMaker* MainNav;
	std::vector<ShooterAI*> Enemies;
	bool isStarted = false;
};