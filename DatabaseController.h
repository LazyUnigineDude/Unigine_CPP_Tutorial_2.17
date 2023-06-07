#pragma once
#include "Unigine.h"

class DatabaseController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(DatabaseController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(Node, DatabaseNode)

		const char* GetName(int& ID);
		int GetValue(int& ID);
		const char* GetImagePath(int& ID);

		DatabaseController* GetDatabase() { return getComponent<DatabaseController>(Unigine::World::getNodeByID(GetRefNum())); }

protected:
	void Init();
	void Update();

private:
	const int GetRefNum() { return 674460560; }
	Unigine::PropertyParameterPtr Parameter;
};
