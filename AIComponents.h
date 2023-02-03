#pragma once
#include <Unigine.h>
#include "Bullet.h"
#include <string>

class DetectionMaker {

public:
	DetectionMaker() = default;
	DetectionMaker(
		Unigine::NodePtr PhysicalTrigger,
		Unigine::NodePtr MainObj,
		Unigine::NodePtr ViewPosition,
		int FieldDistance,
		int Mask);

	void AddCallbacks();
	void CalculateView();
	void RenderView(bool isRender);
	bool TargetVisibleInFrustum(Unigine::NodePtr Target, int Mask, const char* NameDetection);
	void Dodge(bool isDodging, int DodgeDistance);

private:
	void GetObjectsInArea(Unigine::BodyPtr Body);
	bool ObjectNameCheck(Unigine::BodyPtr Body);
	bool ObjectNameCheck(Unigine::ObjectPtr Body);
	void UpdateMainObj(Unigine::Math::Vec3 AddedPosition);

	Unigine::Math::mat4 Frustum;
	Unigine::Math::Mat4 View;
	Unigine::Math::quat Rotation;
	bool isDodging = false;
	std::string MainObjName;

	Unigine::PhysicalTriggerPtr DetectionArea;
	Unigine::Math::BoundFrustum FrustumBound;
	Unigine::NodePtr MainObj, Target, ViewPosition;
	int FieldDistance, Mask, DodgeDistance;
};

class AIGunHandler {

public:
	AIGunHandler() = default;
	AIGunHandler(
		const char* BulletFilePath, 
		int damage,
		Unigine::NodePtr Target,
		Unigine::NodePtr Gun
	);

	void CalculatePositions();
	void Shoot(double TargetSpeed);
	void RenderVisuals(bool isRender, int Mask);

	Unigine::Math::Vec3 FuturePoint;
	Unigine::NodePtr Target, Gun;

	const char* BulletFilePath;
	double FutureDistance, Distance;
	int Damage;
};