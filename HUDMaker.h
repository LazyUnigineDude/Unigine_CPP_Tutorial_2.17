#pragma once
#include <Unigine.h>
#include <string>
#include "HealthBar.h"

class HUDMaker : public Unigine::ComponentBase
{
public: 
	
	COMPONENT_DEFINE(HUDMaker, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		PROP_PARAM(File, CrossHair)
		PROP_PARAM(File, HealthImage)
		PROP_PARAM(Node, MainCharacter)

		void UpdateGun(int CurrentAmount,int MaxAmount); 
		void LoseHealth(int Amount);
		void AddHealth(int Amount);

protected:

	void Init();
	void Update();

private:

	HealthBar* MainCharacterHealth;

	int Width = Unigine::App::getWidth(), Height = Unigine::App::getHeight(), CurrentHealth;
	Unigine::GuiPtr GUI;
	Unigine::WidgetCanvasPtr Canvas;
	Unigine::WidgetSpritePtr Image;
	Unigine::WidgetLabelPtr CurrentAmount, MaxAmount;
	Unigine::WidgetGridBoxPtr Health;
};