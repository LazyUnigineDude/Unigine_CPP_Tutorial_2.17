#pragma once
#include <Unigine.h>
#include <vector>

struct PathMaker {

public:
	PathMaker() = default;

	void AddNewPath(float Duration, std::vector<Unigine::Math::Vec3> PathPoints);
	bool ObjectCloseToPathPoint(Unigine::NodePtr Object, float DistanceLimit);
	bool ObjectCloseToPathPoint(Unigine::NodePtr Object,Unigine::NodePtr Object2, float DistanceLimit);
	void MoveObjectAlongPathPoint(Unigine::NodePtr Object);
	void RenderPath();
	void MovePathPoint(bool isCircuit);
	Unigine::Math::Vec3 GetCurrentPathPosition();
	void RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed);
	void MoveTowards(Unigine::Math::Vec3 MoveTowards, Unigine::NodePtr Obj2Move, int Speed);

private:
	bool InitPath(), ReverseDirection = 0;
	float Weight = 0, DurationTime = 0;
	int num = 0;
	Unigine::SplineGraphPtr Path;
	std::vector<Unigine::Math::Vec3> PathPoints;
};