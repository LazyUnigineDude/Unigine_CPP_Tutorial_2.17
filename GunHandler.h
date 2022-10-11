#pragma once
#include <Unigine.h>
#include "Bullet.h"
#include "HUDMaker.h"

class GunHandler : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(GunHandler, ComponentBase)
		PROP_PARAM(Node, GUNHUD)
		COMPONENT_UPDATE_PHYSICS(Update)
		void GetGun(Unigine::ObjectPtr Gun);
	

protected:
	void Update();

private:

	void Shoot(Unigine::Math::vec3& Lookat);
	void Reload();

	Unigine::ObjectPtr Gun = nullptr;
	float RateofFireTime = 0, RoF = 1;
	bool isHolding = false;
	int CurrentBulletAmount,
		ReloadAmount,
		AmountInGun = 0;

	HUDMaker* HUD;
};