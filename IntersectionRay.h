#pragma once
#include <Unigine.h>


class IntersectionRay : public Unigine::ComponentBase{


public:

	COMPONENT_DEFINE(IntersectionRay,ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)
	PROP_PARAM(Node, PointerNode)

protected:

	void Init();
	void Update();


private:

	Unigine::WorldIntersectionPtr RayPtr;

};

