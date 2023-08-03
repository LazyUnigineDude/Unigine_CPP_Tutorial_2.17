#pragma once
#include <Unigine.h>

class DoorTrigger : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(DoorTrigger, ComponentBase)
		COMPONENT_INIT(Init)

		PROP_PARAM(Node, DoorNode)
		PROP_PARAM(Vec3, ClosePosition)
		PROP_PARAM(Vec3, OpenPosition)

protected:
	void Init();
	void OnEnter(Unigine::BodyPtr Node);
	void OnLeave(Unigine::BodyPtr Node);
	void InitTrigger();
	Unigine::PhysicalTriggerPtr Trigger;
};

class DoorOpener : public DoorTrigger {

public:
	COMPONENT_DEFINE(DoorOpener, DoorTrigger)
		COMPONENT_INIT(Init)
		PROP_PARAM(Node, ButtonNode)
		void OpenDoor();
protected:
	void Init();
	void OnEnter(Unigine::BodyPtr Node);
private:
	bool isOpen = false;
};
