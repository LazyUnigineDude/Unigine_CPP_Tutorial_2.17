#include "AIManager.h"
REGISTER_COMPONENT(AIManager)

void AIManager::Init() {

	// Loop through list points
	// Create Path between points
	// Instantiate AI Give list to AI
	// AI.num == numPaths

	MainNav = getComponent<NavigationMaker>(NavigationNode);
	Enemies.reserve(MainNav->GetNumPaths());

	for (int i = 0; i < MainNav->GetNumPaths(); i++) {
		
		Unigine::NodePtr AI = Unigine::World::loadNode(AINodePrefab.get());
		ShooterAI* _AI = getComponent<ShooterAI>(AI);
		std::vector<Unigine::Math::Vec3> Paths = MainNav->GetPath(i);

		AI->setWorldPosition(Paths[0]);
		_AI->Init(3, Paths, MainCharacter);
		Enemies.push_back(_AI);
	}
}


void AIManager::Update() {

	// input c == foreach AI->update(true)

	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_C) && !isStarted) 
	{ 
		for (auto& i : Enemies) { i->StartAI(); } 
		isStarted = true; 
	}
	if (isStarted) { 
		for (auto& i : Enemies) { i->Update(); } 
	}
}