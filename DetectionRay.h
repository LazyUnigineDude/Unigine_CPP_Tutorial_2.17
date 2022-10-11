#pragma once
#include <Unigine.h>
#include "ShooterAnim.h"

class DetectionRay : public Unigine::ComponentBase {


public:

		COMPONENT_DEFINE(DetectionRay, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(Node, CameraNode)	
		
		
protected:

	void Init();
	void Update();


private:

	Unigine::WorldIntersectionPtr RayPtr;
	Unigine::NodePtr Equip;
};

