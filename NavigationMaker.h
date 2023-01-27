#pragma once
#include <Unigine.h>
#include <vector>

class NavigationMaker : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(NavigationMaker, ComponentBase)
		COMPONENT_INIT(Init)

	struct Paths : Unigine::ComponentStruct{ 
		PROP_ARRAY(Node, PointList) 
		Unigine::Math::Vec3 GetPosition(int Point) { return PointList[Point]->getWorldPosition(); }
	};

	PROP_ARRAY(Node, Obstacles)
		PROP_ARRAY_STRUCT(Paths, PathLists)

	void RenderNavigation();
	std::vector<std::vector<Unigine::Math::Vec3>> GetAllPaths();
	std::vector<Unigine::Math::Vec3> GetPath(int Num);
	std::vector<Unigine::Math::Vec3> GetPath(std::vector<Unigine::Math::Vec3> Points);

protected:
	void Init();

private:

	std::vector<Unigine::Math::Vec3> GetPath(Unigine::PathRoutePtr Path);
	std::vector<std::vector<Unigine::Math::Vec3>> List;
	Unigine::NavigationMeshPtr NavMesh;
};