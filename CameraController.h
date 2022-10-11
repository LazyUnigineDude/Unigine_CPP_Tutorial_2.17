#pragma once

#include <Unigine.h>

class CameraController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CameraController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)

		PROP_PARAM(Toggle, Is_Inverted_Y) // Boolean
		PROP_PARAM(Toggle, Is_Inverted_X)
		PROP_PARAM(Node, LookAtObj)
		PROP_PARAM(Float, Radius)
		PROP_PARAM(Float, Rotation_Speed_Horizontal)
		PROP_PARAM(Float, Rotation_Speed_Vertical)
		PROP_PARAM(Vec2, Min_Max_Height)

protected:
	void Init();
	void Update();

private:

	int Invert_Y, Invert_X;
	float Angle;
	float Height;

	Unigine::PlayerPtr MainCamera;
	Unigine::Math::ivec2 MousePosition;
	Unigine::Math::Vec3 NPoint;

};

