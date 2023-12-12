#pragma once
#include <Unigine.h>
#include <string>
#include "HealthBar.h"

class HUDMaker : public Unigine::ComponentBase
{
public:
	
	COMPONENT_DEFINE(HUDMaker, ComponentBase)
		COMPONENT_INIT(Init, 1)
		COMPONENT_UPDATE(Update, 1)
		COMPONENT_SHUTDOWN(Shutdown, 1)
		PROP_PARAM(File, CrossHair)
		PROP_PARAM(File, HealthImage)
		PROP_PARAM(Node, MainCharacter)

	void UpdateGun(Unigine::Math::ivec2); 
	void HideGun();
	HUDMaker* MainHUD() { return getComponent<HUDMaker>(Unigine::World::getNodeByID(GetRefNum())); }
protected:

	void Init();
	void Update();
	void Shutdown();

private:

	void LoseHealth(int Amount);
	void AddHealth(int Amount);
	HealthBar* MainCharacterHealth;

	const int GetRefNum() { return 245705183; }
	int Width, Height, CurrentHealth;

	Unigine::GuiPtr GUI;
	Unigine::WidgetCanvasPtr Canvas;
	Unigine::WidgetSpritePtr Image;
	Unigine::WidgetLabelPtr CurrentAmount, MaxAmount;
	Unigine::WidgetGridBoxPtr Health;
	Unigine::WidgetLabelPtr Buttons;
};