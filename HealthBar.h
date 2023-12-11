#pragma once
#include <Unigine.h>

class HealthBar : public Unigine::ComponentBase {
public:

	COMPONENT_DEFINE(HealthBar, ComponentBase)
		PROP_PARAM(Int, Health)

		void Init();
		void Init(int Health) ;
		int GetHealth();
		void HealthChange(int amount);

private:
	int health;
};

