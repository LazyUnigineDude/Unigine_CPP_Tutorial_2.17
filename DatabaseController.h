#pragma once
#include "Unigine.h"

class DatabaseController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(DatabaseController, ComponentBase)
		COMPONENT_INIT(Init)
		PROP_PARAM(Node, DatabaseNode)
		enum ITEM_TYPE{ DEFAULT, WEAPON, TRIGGER };

		const char* GetName(int& ID);
		int GetValue(int& ID);
		const char* GetImagePath(int& ID);
		const char* GetPrefabPath(int& ID);
		ITEM_TYPE GetItemType(int& ID);
		DatabaseController* GetDatabase() { return getComponent<DatabaseController>(Unigine::World::getNodeByID(GetRefNum())); }

		struct GUNProps { const char* BulletPath; int Damage, RoF, Reload; };
		GUNProps GetGunProperty(int& ID);
protected:
	void Init();

private:
	const int GetRefNum() { return 1336405277; }
	Unigine::PropertyParameterPtr Parameter;
};
