#pragma once
#include <Unigine.h>

class HealthBar : public Unigine::ComponentBase
{
public:

	COMPONENT_DEFINE(HealthBar, ComponentBase)
		COMPONENT_INIT(Init)
		PROP_PARAM(Int, Health)
		int GetHealth() { return health; }
		void DropHealth(int amount);

protected:
	void Init();

private:
	int health;
	void Check();
};

