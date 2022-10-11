#pragma once

#include <Unigine.h>

class SomeClass : public Unigine::ComponentBase
{

public:

	COMPONENT_DEFINE(SomeClass, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)


protected:

	void Init();
	void Update();

};

