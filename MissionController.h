#pragma once
#include <Unigine.h>

struct MissionController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(MissionController, ComponentBase)
		COMPONENT_INIT(Init)
		PROP_PARAM(Property, MissionProperty)

protected:
	void Init();

private:
	
};