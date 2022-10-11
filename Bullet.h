#pragma once
#include <Unigine.h>

class Bullet : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Bullet, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE_PHYSICS(Update)

	void setDamage(int num) { Damage = num; }

protected:
	void Init();
	void Update();

private:
	float StartTime, LifeTime = 0.4f;
	int Damage = 0;

	Unigine::BodyPtr Body;
	void OnEnter(Unigine::BodyPtr Body, int num);
};

