#include "DoorOpener.h"
REGISTER_COMPONENT(DoorTrigger)
REGISTER_COMPONENT(DoorOpener)

void DoorTrigger::Init() { InitTrigger(); Unigine::Log::message("%s\n",node->getName()); }

void DoorTrigger::OnEnter(Unigine::BodyPtr Node) { 

	Unigine::Log::message("%s Entered\n", Node->getObject()->getName());
	DoorNode->setWorldPosition(Unigine::Math::Vec3(OpenPosition));
}
void DoorTrigger::OnLeave(Unigine::BodyPtr Node) { 
	Unigine::Log::message("%s Left\n", Node->getObject()->getName()); 
	DoorNode->setWorldPosition(Unigine::Math::Vec3(ClosePosition));
}

void DoorTrigger::InitTrigger() {
	Trigger = Unigine::static_ptr_cast<Unigine::PhysicalTrigger>(node);
	if (Trigger) {
		Trigger->addEnterCallback(Unigine::MakeCallback(this, &DoorTrigger::OnEnter));
		Trigger->addLeaveCallback(Unigine::MakeCallback(this, &DoorTrigger::OnLeave));
	}
}

void DoorOpener::Init() {
	Unigine::Log::message("Hi\n");

	Trigger = Unigine::static_ptr_cast<Unigine::PhysicalTrigger>(node);
	if (Trigger) {
		Trigger->addEnterCallback(Unigine::MakeCallback(this, &DoorOpener::OnEnter));
	}
}

void DoorOpener::OnEnter(Unigine::BodyPtr Node) {

	Unigine::Log::message("%s Entered\n", Node->getObject()->getName());
	OpenDoor();
}

void DoorOpener::OpenDoor() {
	isOpen = (!isOpen) ? 1 : 0;
	(!isOpen) ?
		DoorNode->setWorldPosition(Unigine::Math::Vec3(OpenPosition)) :
		DoorNode->setWorldPosition(Unigine::Math::Vec3(ClosePosition));
}