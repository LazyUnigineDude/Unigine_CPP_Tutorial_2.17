#include "PathMaker.h"

bool PathMaker::InitPath() {

	Path = Unigine::SplineGraph::create();

	for (int i = 0; i < PathPoints.size();  i++) { Path->addPoint(PathPoints[i]); }
	for (int i = 0; i < PathPoints.size(); i++) {

		int num = i % Path->getNumPoints(), 
			num2 = (i+1) % Path->getNumPoints();

		Path->addSegment(
			num, 
			Unigine::Math::vec3(PathPoints[num2]) - Unigine::Math::vec3(PathPoints[num]),
			Unigine::Math::vec3_up,
			num2,
			Unigine::Math::vec3(PathPoints[num]) - Unigine::Math::vec3(PathPoints[num2]),
			Unigine::Math::vec3_up
		);
	}

	if (Path->getNumPoints() > 0) return true;
	else return false;
}

void PathMaker::MovePathPoint(bool isCircuit) {

	if (isCircuit) {
		if (!ReverseDirection) {
			Weight = Unigine::Math::clamp(Weight += (Unigine::Game::getIFps() / DurationTime), 0.0f, 1.0f);
			if (Weight == 1.0f) { num++, Weight = 0.0f; }
			if (num == Path->getNumPoints() - 1) { Weight == 1.0f; ReverseDirection = true; }
		}	
		else {
			Weight = Unigine::Math::clamp(Weight -= (Unigine::Game::getIFps() / DurationTime), 0.0f, 1.0f);
			if (Weight == 0.0f) { num--, Weight = 1.0f; }
			if (num < 0) { Weight == 0.0f; ReverseDirection = false; }
		}
	}
	else {
		Weight = Unigine::Math::clamp(Weight += (Unigine::Game::getIFps() / DurationTime), 0.0f, 1.0f);
		if (Weight == 1.0f) { Weight = 0; num++; }
		num %= Path->getNumPoints();
	}
}

Unigine::Math::Vec3 PathMaker::GetCurrentPathPosition() { return Path->calcSegmentPoint(num, Weight); }

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

void PathMaker::AddNewPath(float DurationTime, std::vector<Unigine::Math::Vec3> PathPoints) {
	
	if(Path) Path->deleteLater();
	this->DurationTime = DurationTime;
	this->PathPoints = PathPoints;
    InitPath();
}

bool PathMaker::ObjectCloseToPathPoint(Unigine::NodePtr Object, float DistanceLimit) {

	return (Unigine::Math::distance(
		Unigine::Math::vec3(Object->getWorldPosition()),
		Unigine::Math::vec3(GetCurrentPathPosition())) >= DistanceLimit) ?
		true :
		false;
}

bool PathMaker::ObjectCloseToPathPoint(Unigine::NodePtr Object, Unigine::NodePtr Object2, float DistanceLimit) {

	return (Unigine::Math::distance(
		Unigine::Math::vec3(Object->getWorldPosition()),
		Unigine::Math::vec3(Object2->getWorldPosition())) <= DistanceLimit) ?
		true :
		false;
}

void PathMaker::MoveObjectAlongPathPoint(Unigine::NodePtr Object) {

	Unigine::Math::Vec3
		Point = Path->calcSegmentPoint(num, Weight);
	Unigine::Math::vec3
		Dir = Path->calcSegmentTangent(num, Weight),
		Up = Path->calcSegmentUpVector(num, Weight);

	Object->setWorldPosition(Point);
	Object->setWorldDirection(Dir, Up, Unigine::Math::AXIS_Y);
}

void PathMaker::RenderPath() {

	const int segments = 20;

	for (int i = 0; i < Path->getNumPoints(); i++)
	{
		Unigine::Math::Vec3 Point = Path->getPoint(i);
		Unigine::Visualizer::renderPoint3D(Point, 0.1f, Unigine::Math::vec4_black);

		Unigine::Math::Vec3
			SPoint = Path->getSegmentStartPoint(i),
			EPoint = Path->getSegmentEndPoint(i),
			STang = Unigine::Math::Vec3(Path->getSegmentStartTangent(i)),
			ETang = Unigine::Math::Vec3(Path->getSegmentEndTangent(i));

		//Unigine::Visualizer::renderVector(SPoint, SPoint + STang, Unigine::Math::vec4_green);
		//Unigine::Visualizer::renderVector(EPoint, EPoint + ETang, Unigine::Math::vec4_red);

		for (int j = 0; j < segments; j++)
		{
			Unigine::Math::Vec3
				p0 = Path->calcSegmentPoint(i, j / segments),
				p1 = Path->calcSegmentPoint(i, (j +1) / segments);

			//Unigine::Visualizer::renderVector(p0, p1, Unigine::Math::vec4_white);
		}
		Unigine::Visualizer::renderPoint3D(GetCurrentPathPosition(), 0.1f, Unigine::Math::vec4_red);
	}
}