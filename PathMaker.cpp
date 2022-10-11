#include "PathMaker.h"
REGISTER_COMPONENT(PathMaker)

void PathMaker::InitPath() {

	Path = Unigine::SplineGraph::create();

	for (int i = 0; i < PathPoints.size();  i++) { Path->addPoint(PathPoints[i]->getWorldPosition()); }
	for (int i = 0; i < PathPoints.size(); i++)
	{
		int num = i % Path->getNumPoints(), num2 = (i+1) % Path->getNumPoints();
		Path->addSegment(num, PathPoints[num]->getWorldDirection(Unigine::Math::AXIS_Y), PathPoints[num]->getWorldDirection(Unigine::Math::AXIS_Z),
						 num2, PathPoints[num2]->getWorldDirection(Unigine::Math::AXIS_NY), PathPoints[num2]->getWorldDirection(Unigine::Math::AXIS_Z));
	}
}

void PathMaker::MoveAlongPath() {
	
	Weight = Unigine::Math::clamp(Weight += (Unigine::Game::getIFps() / DurationTime), 0.0f, 1.0f);
	if (Weight == 1.0f) { Weight = 0; num++; }
	num %= Path->getNumPoints();
}

Unigine::Math::vec3 PathMaker::GetCurrentPathPosition() 
{ return Path->calcSegmentPoint(num, Weight); }

void PathMaker::MoveObject(Unigine::NodePtr Object) {

	Unigine::Math::vec3
		Point = Path->calcSegmentPoint(num, Weight),
		Dir = Path->calcSegmentTangent(num, Weight),
		Up = Path->calcSegmentUpVector(num, Weight);

	Object->setWorldPosition(Point);
	Object->setWorldDirection(Dir, Up, Unigine::Math::AXIS_Y);
}

void PathMaker::RenderPath() { 

	const int segments = 50;

	for (int i = 0; i < Path->getNumPoints(); i++)
	{
		Unigine::Math::vec3 Point = Path->getPoint(i);
		Unigine::Visualizer::renderPoint3D(Point, 0.1f, Unigine::Math::vec4_black);

		Unigine::Math::vec3
			SPoint = Path->getSegmentStartPoint(i),
			STang = Path->getSegmentStartTangent(i),
			EPoint = Path->getSegmentEndPoint(i),
			ETang = Path->getSegmentEndTangent(i);

		Unigine::Visualizer::renderVector(SPoint, SPoint + STang, Unigine::Math::vec4_green);
		Unigine::Visualizer::renderVector(EPoint, EPoint + ETang, Unigine::Math::vec4_red);

		for (int j = 0; j < segments; j++)
		{
			Unigine::Math::vec3
				p0 = Path->calcSegmentPoint(i, j / segments),
				p1 = Path->calcSegmentPoint(i, (j +1) / segments);

			Unigine::Visualizer::renderLine3D(p0, p1, Unigine::Math::vec4_white);
		}
	}
}