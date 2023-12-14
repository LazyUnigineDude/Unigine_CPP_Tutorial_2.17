#include "TurretClass.h"
REGISTER_COMPONENT(TurretClass)

void TurretClass::Init() {

	HealthBar* H = getComponent<HealthBar>(HealthBarNode);
	H->Init();
	CurHealth = H->GetHealth();
	MaxHealth = H->GetHealth();
	Health.push_back(H);

	LabelGUI = Unigine::ObjectGui::create(2, 2);
	LabelGUI->setBillboard(1);
	LabelGUI->setBackground(0);
	LabelGUI->setScreenSize(100, 50);

	std::string Label = std::to_string(CurHealth) +" / " + std::to_string(MaxHealth);
	HealthLabel = Unigine::WidgetLabel::create(Label.c_str());
	HealthLabel->setFontOutline(2);
	HealthLabel->setFontColor(Unigine::Math::vec4_red);
	HealthLabel->setFontSize(28);
	LabelGUI->getGui()->addChild(HealthLabel, Unigine::Gui::ALIGN_EXPAND | Unigine::Gui::ALIGN_OVERLAP);

	LabelGUI->setParent(HealthBarNode);
	LabelGUI->setPosition(Unigine::Math::Vec3(0, 2, 8));


	Detection = DetectionMaker(nullptr, RotObj, ShootArea, 150, 0);
	Sound = getComponent<SoundController>(SoundNode);
	Sound->Init();
	IdleSound = getComponent<SoundController>(IdleSoundNode);
	IdleSound->Init();
	IdleSound->PlaySound();
	Particle = Unigine::static_ptr_cast<Unigine::ObjectParticles>(ParticleNode.get());
}

void TurretClass::Update() {

	// Logic 
	if (CurHealth <= 0) { ClearGUI(); if(State != DESTROYED) State = DESTROYED; }
	Detection.CalculateView();
	if (State != DESTROYED) Detection.RenderView(true);

	// HealthGUI Update
	for (int i = 0; i < Health.size(); i++) {
		if (Health[i]->GetHealth() < CurHealth) {

			if (State != ATTACK) State = ATTACK;

			CurHealth -= (CurHealth - Health[i]->GetHealth());
			std::string Label = std::to_string(CurHealth) + " / " + std::to_string(MaxHealth);
			if (HealthLabel) HealthLabel->setText(Label.c_str());
		}
	}

	auto isVisible = [&]() {
		if (Detection.TargetVisibleInFrustum(EnemyNode, 0)) {

			Unigine::ObjectPtr Obj = Unigine::World::getIntersection(
				ShootArea->getWorldPosition(),
				EnemyNode->getWorldPosition(),
				MaskNode
			);

			if (Obj && strcmp(Obj->getName(), "MainCharacter") == 0) return true;
			return false;
		}
	};

	switch (State) {

	case TurretClass::SEARCH:
		RotObj->worldRotate(0,0,Unigine::Game::getIFps() * Speed);
		if (isVisible()) {
				State = ATTACK;
				CurrTime = Unigine::Game::getTime() + (1 / RoF);
		}		
		break;

	case TurretClass::ATTACK:
		RotObj->worldLookAt(EnemyNode->getWorldPosition());
		ShootArea->worldLookAt(CalculatePosition());
		Unigine::Visualizer::renderLine3D(ShootArea->getWorldPosition(), ShootArea->getWorldPosition() + Unigine::Math::Vec3(ShootArea->getWorldDirection(Unigine::Math::AXIS_Y) * 100), Unigine::Math::vec4_red);
		if (!isVisible()) State = SEARCH;

		if (CurrTime < Unigine::Game::getTime() ) {
			// Shoot
			Sound->PlaySound();
			CurrTime = Unigine::Game::getTime() + (1 / RoF);
			Unigine::String X = Bullet.get();
			Unigine::NodePtr _Bullet = Unigine::World::loadNode(Bullet);
			_Bullet->setWorldPosition(ShootArea->getWorldPosition());
			_Bullet->setWorldRotation(ShootArea->getWorldRotation());
			_Bullet->getObjectBodyRigid()->addLinearImpulse(ShootArea->getWorldDirection(Unigine::Math::AXIS_Y) * 5000);
		}
		break;

	case TurretClass::DESTROYED:
		if (Particle->isEnabled() == 0) Particle->setEnabled(1);
		if (IdleSound->isPlaying()) IdleSound->StopSound();
		HealthBarNode->setRotation(Unigine::Math::quat(50,35,0));
		break;

	default: break; }
}

void TurretClass::Shutdown() { ClearGUI(); }

void TurretClass::ClearGUI() {

	if (LabelGUI) { 
		if (HealthLabel && LabelGUI->getGui()->isChild(HealthLabel)) { LabelGUI->getGui()->removeChild(HealthLabel); }
		LabelGUI->deleteLater(); LabelGUI = nullptr;
	}
	if (HealthLabel) { HealthLabel->deleteLater(); HealthLabel = nullptr; }
}

Unigine::Math::Vec3 TurretClass::CalculatePosition() {

	return EnemyNode->getWorldPosition() +
		Unigine::Math::Vec3(EnemyNode->getParent()->getBodyLinearVelocity().normalize());
}