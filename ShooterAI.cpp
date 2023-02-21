#include "ShooterAI.h"
REGISTER_COMPONENT(ShooterAI)

void ShooterAI::Init() {

	Health = getComponent<HealthBar>(node);
	CurrentHealth = 15;

	Detector = DetectionMaker(
		PhysicalTriggerNode,
		node,
		node->getChild(0),
		FIELD_DISTANCE,
		MASK_PRIMARY
	);
	Detector.AddCallbacks();

	GunHandler = AIGunHandler(
		BulletPrefab.get(),
		DAMAGE,
		MainCharacter,
		node->getChild(0)
	);

	MainNav = getComponent<NavigationMaker>(PathFindingNode);
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

	if (CurrentHealth != Health->GetHealth() && CanMove) { ChangeState(AGGRESSIVE); Weight = 1.0f; CurrentHealth = Health->GetHealth(); }

	switch (STATE)
	{
	case ShooterAI::IDLE:
		//Unigine::Log::message("IDLE\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps(), 0.0f, 1.0f);
		if (isVisible) { ChangeState(CurrentState::ALERT); }
		if (Unigine::Input::isKeyDown(Unigine::Input::KEY_C)) { // Event to start checking
				MainPath.AddNewPath(3, MainNav->GetPath(0));
			CanMove = true;
		}
		if (CanMove) {
			MainPath.RenderPath();
			if (MainPath.ObjectCloseToPathPoint(node, 0.1f)) {
				MainPath.RotateTowards(MainPath.GetCurrentPathPosition(), node, 0.05f);
				MainPath.MoveTowards(MainPath.GetCurrentPathPosition(), node, 5);
			}
			else {
				MainPath.MovePathPoint(true);
				MainPath.MoveObjectAlongPathPoint(node);
			}
		}
		break;
	case ShooterAI::ALERT:
		Weight = Unigine::Math::clamp(Weight += Unigine::Game::getIFps() / DistanceFactor, 0.0f, 1.0f);
		if (Weight == 1.0f) { ChangeState(CurrentState::AGGRESSIVE); }
		if (!isVisible) { ChangeState(CurrentState::IDLE); }
				MainPath.RotateTowards(MainCharacter->getWorldPosition(), node, 0.005f);
		break;
	case ShooterAI::SEARCH:
		//Unigine::Log::message("SRCH\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps() / 5, 0.0f, 1.0f);
		if (Weight == 0.0f) { ChangeState(CurrentState::IDLE); }
		if (isVisible) { ChangeState(CurrentState::AGGRESSIVE); Weight = 1; }
				MainPath.RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
				MainPath.MoveTowards(MainCharacter->getWorldPosition(), node, 3);
		break;
	case ShooterAI::AGGRESSIVE:
		//Unigine::Log::message("AGRO\n");
		if (!isVisible) { ChangeState(CurrentState::SEARCH); }
				MainPath.RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
				MainPath.MoveTowards(MainCharacter->getWorldPosition(), node, 5);
		if (MainPath.ObjectCloseToPathPoint(node, MainCharacter, 20)) { ChangeState(SHOOT); CurrentTime = Unigine::Game::getTime(); }
		break;
	case ShooterAI::SHOOT:
		if (CurrentTime + 1 < Unigine::Game::getTime()) { Shoot(); ChangeState(AGGRESSIVE); }
			MainPath.RotateTowards(MainCharacter->getWorldPosition(), node, 0.02f);
			//Unigine::Visualizer::renderLine3D(node->getWorldPosition(), node->getWorldPosition() + Unigine::Math::Vec3(node->getWorldDirection(Unigine::Math::AXIS_Y)) * 20, Unigine::Math::vec4_blue);
		break;
	case ShooterAI::DODGE:
			Detector.Dodge(true, 10);
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