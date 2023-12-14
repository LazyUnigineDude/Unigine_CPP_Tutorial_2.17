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
		PROP_PARAM(Node, HealthBarNode)
		PROP_PARAM(Node, SoundNode)
		PROP_PARAM(Node, IdleSoundNode)
		PROP_PARAM(Node, ParticleNode)

	bool isDestroyed() { return State == DESTROYED; }
	bool isAttacking() { return State == ATTACK; }

protected:
	void Init(), Update(), Shutdown();

private:
	SoundController* Sound, *IdleSound;
	void ClearGUI();

	enum STATE { SEARCH, ATTACK, DESTROYED };
	STATE State = SEARCH;
	int Speed = 5, MaxHealth, CurHealth;;
	float RoF = 0.5f, CurrTime = 0;
	DetectionMaker Detection;
	Unigine::Vector<HealthBar*> Health;
	Unigine::ObjectGuiPtr LabelGUI;
	Unigine::WidgetLabelPtr HealthLabel;
	Unigine::ObjectParticlesPtr Particle;
	Unigine::Math::Vec3 CalculatePosition();
};