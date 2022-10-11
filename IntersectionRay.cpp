#include "IntersectionRay.h"

REGISTER_COMPONENT(IntersectionRay)


void IntersectionRay::Init() { 
	RayPtr = Unigine::WorldIntersection::create();
}

void IntersectionRay::Update() {

	Unigine::ObjectPtr IObj = Unigine::World::getIntersection(
		PointerNode.get()->getWorldPosition(),
		Unigine::Game::getPlayer()->getWorldDirection() * 100,
		1,
		RayPtr
	);


	if (IObj) {
		Unigine::Console::message("Name: %s \n", IObj.get()->getName());
	}
}