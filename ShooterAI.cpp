#include "ShooterAI.h"
REGISTER_COMPONENT(ShooterAI)
#include "PhysicsController.h"

void ShooterAI::Init() {

	Health = getComponent<HealthBar>(node);
	CurrentHealth = 15;

	Detector = DetectionMaker(
		PhysicalTriggerNode.get(),
		node,
		node->getChild(0),
		FIELD_DISTANCE,
		MASK_PRIMARY
	);

	GunHandler = AIGunHandler(
		BulletPrefab.get(),
		DAMAGE,
		MainCharacter,
		node->getChild(0)
	);
}

void ShooterAI::Update() {

		Detector.CalculateView();
		Detector.RenderView(true);
		isVisible = Detector.TargetVisibleInFrustum(MainCharacter, MASK_PRIMARY, MainCharacter->getChild(0)->getName());

	float distance = Unigine::Math::distance(
		Unigine::Math::vec3(MainCharacter->getWorldPosition()), 
		Unigine::Math::vec3(node->getWorldPosition()));

	DistanceFactor = distance / FIELD_DISTANCE;

		AiState();
}

void ShooterAI::AiState() {

	//if (CurrentHealth != Health->GetHealth()) { ChangeState(AGGRESSIVE); Weight = 1.0f; CurrentHealth = Health->GetHealth(); }

	switch (STATE)
	{
	case ShooterAI::IDLE:
		//Unigine::Log::message("IDLE\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps(), 0.0f, 1.0f);
		//if (isVisible) { ChangeState(CurrentState::ALERT); }
			/*if (Unigine::Math::distance(Unigine::Math::vec3(node->getWorldPosition()), Unigine::Math::vec3(Path->GetCurrentPathPosition())) > 0.1f) {
				RotateTowards(Path->GetCurrentPathPosition(), node, 0.05f);
				MoveTowards(Path->GetCurrentPathPosition(), node, 1);
			}
			else {
				Path->MoveAlongPath();
				Path->MoveObject(node);
			}*/
		break;
	case ShooterAI::ALERT:
		//Unigine::Log::message("ALRT\n");
		Weight = Unigine::Math::clamp(Weight += Unigine::Game::getIFps() / DistanceFactor, 0.0f, 1.0f);
		if (Weight == 1.0f) { ChangeState(CurrentState::AGGRESSIVE); }
		if (!isVisible) { ChangeState(CurrentState::IDLE); }
			//RotateTowards(MainCharacter->getWorldPosition(), node, 0.005f);
		break;
	case ShooterAI::SEARCH:
		//Unigine::Log::message("SRCH\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps() / 5, 0.0f, 1.0f);
		if (Weight == 0.0f) { ChangeState(CurrentState::IDLE); }
		if (isVisible) { ChangeState(CurrentState::AGGRESSIVE); Weight = 1; }
			//RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
			//MoveTowards(MainCharacter->getWorldPosition(), node, 3);
		break;
	case ShooterAI::AGGRESSIVE:
		//Unigine::Log::message("AGRO\n");
		if (!isVisible) { ChangeState(CurrentState::SEARCH); }
		//	RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
			//MoveTowards(MainCharacter->getWorldPosition(), node, 5);
			if (Unigine::Math::distance(Unigine::Math::vec3(node->getWorldPosition()), Unigine::Math::vec3(MainCharacter->getWorldPosition())) < 20.0f) { ChangeState(SHOOT); CurrentTime = Unigine::Game::getTime(); }
		break;
	case ShooterAI::SHOOT:
			if (CurrentTime + 1 < Unigine::Game::getTime()) { Shoot(); ChangeState(AGGRESSIVE); }
			//RotateTowards(MainCharacter->getWorldPosition(), node, 0.02f);
			Unigine::Visualizer::renderLine3D(node->getWorldPosition(), node->getWorldPosition() + Unigine::Math::Vec3(node->getWorldDirection(Unigine::Math::AXIS_Y)) * 20, Unigine::Math::vec4_blue);
		break;
	case ShooterAI::DODGE:
		break;
	default: break;
	}
}

void ShooterAI::Shoot() {

	double Speed = getComponent<PhysicsController>(MainCharacter)->getSpeed();

	GunHandler.CalculatePositions();
	GunHandler.RenderVisuals(true, MASK_SECONDARY);
	GunHandler.Shoot(Speed);
}