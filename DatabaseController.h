#pragma once
#include "Unigine.h"

class DatabaseController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(DatabaseController, ComponentBase)
		COMPONENT_INIT(Init)
		PROP_PARAM(Node, DatabaseNode)

		const char* GetName(int& ID);
		int GetValue(int& ID);
		const char* GetImagePath(int& ID);
		DatabaseController* GetDatabase() { return getComponent<DatabaseController>(Unigine::World::getNodeByID(GetRefNum())); }
		const char* GetPrefabPath(int& ID);

protected:
	void Init();

private:
	const int GetRefNum() { return 674460560; }
	Unigine::PropertyParameterPtr Parameter;
};
