#include "TurretClass.h"
REGISTER_COMPONENT(TurretClass)

void TurretClass::Init() {

	for (int i = 0; i < HealthBarNode.size(); i++) {
		HealthBar* H = getComponent<HealthBar>(HealthBarNode[i]);
		H->Init();
		CurHealth.push_back(H->GetHealth());
		MaxHealth.push_back(H->GetHealth());
		TotalHealth += H->GetHealth();
		Health.push_back(H);

		Unigine::ObjectGuiPtr _GUI = Unigine::ObjectGui::create(2, 2);
		_GUI->setBillboard(1);
		_GUI->setBackground(0);
		_GUI->setScreenSize(100, 50);

		std::string Label = std::to_string(H->GetHealth()) +" / " + std::to_string(MaxHealth[i]);
		Unigine::WidgetLabelPtr _Health = Unigine::WidgetLabel::create(Label.c_str());
		_Health->setFontOutline(2);
		_Health->setFontColor(Unigine::Math::vec4_red);
		_Health->setFontSize(28);
		_GUI->getGui()->addChild(_Health, Unigine::Gui::ALIGN_EXPAND | Unigine::Gui::ALIGN_OVERLAP);

		_GUI->setParent(HealthBarNode[i]);
		_GUI->setPosition(Unigine::Math::Vec3(0, 2, 8 - i));

		LabelGUI.push_back(_GUI);
		HealthLabel.push_back(_Health);
	}


	Detection = DetectionMaker(nullptr, RotObj, ShootArea, 150, 0);
}

void TurretClass::Update() {

	if (TotalHealth == 0) { ClearGUI(); node->deleteLater(); return; }
	Detection.CalculateView();
	Detection.RenderView(true);

	for (int i = 0; i < MaxHealth.size(); i++) {
		if (Health[i]->GetHealth() < CurHealth[i]) {

			if (State != ATTACK) State = ATTACK;

			TotalHealth -= (CurHealth[i] - Health[i]->GetHealth());
			CurHealth[i] = Health[i]->GetHealth();

			std::string Label = std::to_string(CurHealth[i]) + " / " + std::to_string(MaxHealth[i]);
			if (HealthLabel[i]) HealthLabel[i]->setText(Label.c_str());
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
		ShootArea->worldLookAt(EnemyNode->getWorldPosition());
		Unigine::Visualizer::renderLine3D(ShootArea->getWorldPosition(), ShootArea->getWorldPosition() + Unigine::Math::Vec3(ShootArea->getWorldDirection(Unigine::Math::AXIS_Y) * 100), Unigine::Math::vec4_red);
		if (!isVisible()) State = SEARCH;

		if (CurrTime < Unigine::Game::getTime() ) {
			CurrTime = Unigine::Game::getTime() + (1 / RoF);
			Unigine::String X = Bullet.get();
			Unigine::NodePtr _Bullet = Unigine::World::loadNode(Bullet);
			_Bullet->setWorldPosition(ShootArea->getWorldPosition());
			_Bullet->setWorldRotation(ShootArea->getWorldRotation());
			_Bullet->getObjectBodyRigid()->addLinearImpulse(ShootArea->getWorldDirection(Unigine::Math::AXIS_Y) * 50);
		}
		break;

	default: break; }

}

void TurretClass::Shutdown() { ClearGUI(); }

void TurretClass::ClearGUI() {
	for (auto& i : LabelGUI) {
		for (auto& j : HealthLabel) {

			if (i->getGui()->isChild(j)) {
				i->getGui()->removeChild(j);
				j->deleteLater();
			}
		}
		i->deleteLater();
	}
	LabelGUI.clear();
	HealthLabel.clear();
}