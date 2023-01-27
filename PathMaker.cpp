#include "PathMaker.h"

inline PathMaker::PathMaker(
	float DurationTime,
	std::vector<Unigine::Math::Vec3> PathPoints) {

	this->PathPoints = PathPoints;
	this->DurationTime = DurationTime;
}

inline void PathMaker::InitPath() {

	Path = Unigine::SplineGraph::create();

	for (int i = 0; i < PathPoints.size();  i++) { Path->addPoint(PathPoints[i]); }
	for (int i = 0; i < PathPoints.size(); i++) {
		
		int num = i % Path->getNumPoints(), 
			num2 = (i+1) % Path->getNumPoints();

		Path->addSegment(
			num, 
			Unigine::Math::vec3(PathPoints[num2]) - Unigine::Math::vec3(PathPoints[num]),
			Unigine::Math::vec3_up,
			num,
			Unigine::Math::vec3(PathPoints[num]) - Unigine::Math::vec3(PathPoints[num2]),
			Unigine::Math::vec3_up
		);
	}
}

inline void PathMaker::MoveAlongPath() {
	
	Weight = Unigine::Math::clamp(Weight += (Unigine::Game::getIFps() / DurationTime), 0.0f, 1.0f);
	if (Weight == 1.0f) { Weight = 0; num++; }
	num %= Path->getNumPoints();
}

inline Unigine::Math::Vec3 PathMaker::GetCurrentPathPosition() { return Path->calcSegmentPoint(num, Weight); }

void PathMaker::RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed) {
	
	Unigine::Math::vec3 Vec1 = Obj2Move->getWorldDirection(Unigine::Math::AXIS_Y),
		Vec2 = Unigine::Math::vec3((RotateTowards - Obj2Move->getWorldPosition())).normalize();

	float Angle = Unigine::Math::getAngle(Vec1, Vec2, Unigine::Math::vec3_up);
	Obj2Move->rotate(-Obj2Move->getWorldRotation().x, -Obj2Move->getWorldRotation().y, Angle * RoatateSpeed);
}

void PathMaker::MoveTowards(Unigine::Math::Vec3 MoveTowards, Unigine::NodePtr Obj2Move, int Speed) {
	
	Unigine::Math::Vec3 Pos = Unigine::Math::lerp(
		Obj2Move->getWorldPosition(),
		MoveTowards,
		Unigine::Game::getIFps() * Speed /
		Unigine::Math::distance(Unigine::Math::vec3(Obj2Move->getWorldPosition()), Unigine::Math::vec3(MoveTowards)));
	Obj2Move->setWorldPosition(Pos);
}

inline void PathMaker::MoveObject(Unigine::NodePtr Object) {

	Unigine::Math::Vec3
		Point = Path->calcSegmentPoint(num, Weight);
	Unigine::Math::vec3
		Dir = Path->calcSegmentTangent(num, Weight),
		Up = Path->calcSegmentUpVector(num, Weight);

	Object->setWorldPosition(Point);
	Object->setWorldDirection(Dir, Up, Unigine::Math::AXIS_Y);
}

inline void PathMaker::RenderPath() {

	const int segments = 50;

	for (int i = 0; i < Path->getNumPoints(); i++)
	{
		Unigine::Math::Vec3 Point = Path->getPoint(i);
		Unigine::Visualizer::renderPoint3D(Point, 0.1f, Unigine::Math::vec4_black);

		Unigine::Math::Vec3
			SPoint = Path->getSegmentStartPoint(i),
			EPoint = Path->getSegmentEndPoint(i),
			STang = Unigine::Math::Vec3(Path->getSegmentStartTangent(i)),
			ETang = Unigine::Math::Vec3(Path->getSegmentEndTangent(i));

		Unigine::Visualizer::renderVector(SPoint, SPoint + STang, Unigine::Math::vec4_green);
		Unigine::Visualizer::renderVector(EPoint, EPoint + ETang, Unigine::Math::vec4_red);

		for (int j = 0; j < segments; j++)
		{
			Unigine::Math::Vec3
				p0 = Path->calcSegmentPoint(i, j / segments),
				p1 = Path->calcSegmentPoint(i, (j +1) / segments);

			Unigine::Visualizer::renderLine3D(p0, p1, Unigine::Math::vec4_white);
		}
	}
}