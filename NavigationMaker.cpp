#include "NavigationMaker.h"
REGISTER_COMPONENT(NavigationMaker)

void NavigationMaker::RenderNavigation() {

	if(NavMesh == nullptr) NavMesh = Unigine::static_ptr_cast<Unigine::NavigationMesh>(node);
	NavMesh->renderVisualizer();
}

std::vector<std::vector<Unigine::Math::Vec3>> NavigationMaker::GetAllPaths() { return List; }
std::vector<Unigine::Math::Vec3> NavigationMaker::GetPath(int Num) { return List[Num]; }
std::vector<Unigine::Math::Vec3> NavigationMaker::GetPath(std::vector<Unigine::Math::Vec3> Points) {
	
	std::vector<Unigine::Math::Vec3> NewPoints;
	Unigine::PathRoutePtr Path = Unigine::PathRoute::create();

	for (int i = 0; i < Points.size() - 1; i++) {

		Path->create2D(Points[i], Points[i + 1]);
		std::vector<Unigine::Math::Vec3> _Points = GetPath(Path);
		NewPoints.insert(NewPoints.end(), _Points.begin(), _Points.end());
	}
	
	return NewPoints;
}

std::vector<Unigine::Math::Vec3> NavigationMaker::GetPath(Unigine::PathRoutePtr Path) {
	
	std::vector<Unigine::Math::Vec3> Points;
	for (int k = 0; k < Path->getNumPoints(); k++) {
		Points.push_back(Path->getPoint(k));
	}
	return Points;
}

void NavigationMaker::Init() {

	Unigine::PathRoutePtr Path = Unigine::PathRoute::create();

	for (int i = 0; i < PathLists.size(); i++) {
		for (int j = 0; j < PathLists[i]->PointList.size() - 1; j++) {

			Path->create2D(PathLists[i]->GetPosition(j), PathLists[i]->GetPosition(j + 1));
			List.push_back(GetPath(Path));
		}
	}

	Path->deleteLater();
}
