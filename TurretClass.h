#pragma once
#include <Unigine.h>
#include "HealthBar.h"
#include "AIComponents.h"
#include "SoundController.h"

class TurretClass : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(TurretClass, ComponentBase)
		COMPONENT_INIT(Init, 1)
		COMPONENT_UPDATE(Update, 1)
		COMPONENT_SHUTDOWN(Shutdown, 1)
		PROP_PARAM(Node, RotObj)
		PROP_PARAM(Node, ShootArea)
		PROP_PARAM(Node, EnemyNode)
		PROP_PARAM(File, Bullet)
		PROP_PARAM(Mask, MaskNode)
		PROP_ARRAY(Node, HealthBarNode)
		PROP_PARAM(Node, SoundNode)

protected:
	void Init(), Update(), Shutdown();

private:
	SoundController* Sound;
	void ClearGUI();
	Unigine::Math::Vec3 CalculatePosition();

	enum STATE { SEARCH, ATTACK };
	STATE State = SEARCH;
	Unigine::Vector<HealthBar*> Health;
	int Speed = 5, TotalHealth;
	float RoF = 0.5f, CurrTime = 0;
	DetectionMaker Detection;
	Unigine::Vector<Unigine::ObjectGuiPtr> LabelGUI;
	Unigine::Vector<Unigine::WidgetLabelPtr> HealthLabel;
	Unigine::Vector<int> MaxHealth, CurHealth;
};