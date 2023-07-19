#pragma once
#include <Unigine.h>
#include "Bullet.h"
#include "DatabaseController.h"

class GunHandler : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(GunHandler, ComponentBase)
		PROP_PARAM(Node, HandlePosition)

		void Init(Unigine::PlayerPtr Camera);
	void GrabGun(Unigine::Math::ivec2 GunValue);
	void Equip();
	void UnEquip();
	void Shoot(float Time);
	void Reload();
	bool IsHolding() { return isHolding; }
	bool IsGrabbed() { return isGrabbed; }
	Unigine::Math::ivec2 GetGUIValues();

private:

	void Shoot(Unigine::Math::Vec3 Lookat);
	Unigine::PlayerPtr Camera;
	Unigine::NodePtr Gun;
	int AmountInGun = 0;
	float RateofFireTime = 0;
	bool isHolding = false, isGrabbed = false;
	
	Unigine::Math::ivec2 Item;
	DatabaseController::GUNProps GunProperty;
};