#pragma once
#include <Unigine.h>

class PropertyChecker : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(PropertyChecker, ComponentBase)
		COMPONENT_INIT(Init)

protected:
	void Init();

private:
	Unigine::PropertyPtr PropertyPtr;
	Unigine::PropertyParameterPtr ParameterPtr;

};

