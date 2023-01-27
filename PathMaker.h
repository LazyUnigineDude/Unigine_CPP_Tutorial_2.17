#pragma once
#include <Unigine.h>
#include <vector>

class PathMaker {

public:
	PathMaker() = default;
	PathMaker(
		float DurationTime,
		std::vector<Unigine::Math::Vec3> PathPoints);

	void InitPath();
	void MoveObject(Unigine::NodePtr Object);
	void RenderPath();
	void MoveAlongPath();
	Unigine::Math::Vec3 GetCurrentPathPosition();
	void RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed);
	void MoveTowards(Unigine::Math::Vec3 MoveTowards, Unigine::NodePtr Obj2Move, int Speed);

private:

	float Weight = 0, DurationTime = 0;
	int num = 0;
	Unigine::SplineGraphPtr Path;
	std::vector<Unigine::Math::Vec3> PathPoints;
};