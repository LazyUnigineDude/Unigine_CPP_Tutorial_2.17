#pragma once
#include <Unigine.h>

class Bullet : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(Bullet, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE_PHYSICS(Update)
		PROP_PARAM(Int, DamageAmount, 1)

	void setDamage(int num) { DamageAmount = num; }

protected:
	void Init();
	void Update();

private:
	float StartTime, LifeTime = 5.0f;

	Unigine::BodyPtr Body;
	void OnEnter(Unigine::BodyPtr Body, int num);
	void* Callback;
};