#include "ShooterAI.h"
REGISTER_COMPONENT(ShooterAI)

void ShooterAI::Init() {

	Path = getComponent<PathMaker>(PathMakerNode);
	Path->InitPath();
	Health = getComponent<HealthBar>(node);
	CurrentHealth = Health->GetHealth();
}

void ShooterAI::Update() {

	// Calculate the Area, Position and Rotation
	Unigine::Math::mat4 Frustum(Unigine::Math::perspective(40, 1.4f, 0.05, FieldDistance));
		Unigine::Math::quat Rotation(node->getWorldRotation() * Unigine::Math::quat(90, 0, 0));
		Unigine::Math::mat4 View(Rotation, node->getChild(0)->getWorldPosition());
	
		// Render
		Unigine::Visualizer::renderFrustum(Frustum, View, Unigine::Math::vec4_black);
		Unigine::Visualizer::renderVector(node->getWorldPosition(), node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y) * 2, Unigine::Math::vec4_black);

		// Logic
		BFrustum = Unigine::Math::BoundFrustum(Frustum, Unigine::Math::inverse(View));
		if (BFrustum.inside(MainCharacter->getWorldPosition())) {
			isInsideFrustum = true;
			float distance = Unigine::Math::distance(MainCharacter->getWorldPosition(), node->getWorldPosition());
			DistanceFactor = distance / FieldDistance;
		}
		else isInsideFrustum = false;

		AiState();
}

void ShooterAI::AiState() {

	if (CurrentHealth != Health->GetHealth()) { ChangeState(AGGRESSIVE); Weight = 1.0f; CurrentHealth = Health->GetHealth(); }

	switch (STATE)
	{
	case ShooterAI::IDLE:
		//Unigine::Log::message("IDLE\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps(), 0.0f, 1.0f);
		if (isInsideFrustum) { ChangeState(CurrentState::ALERT); }
			if (Unigine::Math::distance(node->getWorldPosition(),Path->GetCurrentPathPosition()) > 0.1f) {
				RotateTowards(Path->GetCurrentPathPosition(), node, 0.05f);
				MoveTowards(Path->GetCurrentPathPosition(), node, 1);
			}
			else {
				Path->MoveAlongPath();
				Path->MoveObject(node);
			}
		break;
	case ShooterAI::ALERT:
		//Unigine::Log::message("ALRT\n");
		Weight = Unigine::Math::clamp(Weight += Unigine::Game::getIFps() / DistanceFactor, 0.0f, 1.0f);
		if (Weight == 1.0f) { ChangeState(CurrentState::AGGRESSIVE); }
		if (!isInsideFrustum) { ChangeState(CurrentState::IDLE); }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.005f);
		break;
	case ShooterAI::SEARCH:
		//Unigine::Log::message("SRCH\n");
		Weight = Unigine::Math::clamp(Weight -= Unigine::Game::getIFps() / 5, 0.0f, 1.0f);
		if (Weight == 0.0f) { ChangeState(CurrentState::IDLE); }
		if (isInsideFrustum) { ChangeState(CurrentState::AGGRESSIVE); Weight = 1; }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
			MoveTowards(MainCharacter->getWorldPosition(), node, 3);
		break;
	case ShooterAI::AGGRESSIVE:
		//Unigine::Log::message("AGRO\n");
		if (!isInsideFrustum) { ChangeState(CurrentState::SEARCH); }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.05f);
			MoveTowards(MainCharacter->getWorldPosition(), node, 5);
			if (Unigine::Math::distance(node->getWorldPosition(), MainCharacter->getWorldPosition()) < 20.0f) { ChangeState(SHOOT); CurrentTime = Unigine::Game::getTime(); }
		break;
	case ShooterAI::SHOOT:
			if (CurrentTime + 1 < Unigine::Game::getTime()) { Shoot(); ChangeState(AGGRESSIVE); }
			RotateTowards(MainCharacter->getWorldPosition(), node, 0.02f);
		break;
	default: break;
	}
}

void ShooterAI::RotateTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, float RoatateSpeed) {

	Unigine::Math::Vec3 Vec1 = Obj2Move->getWorldDirection(Unigine::Math::AXIS_Y),
						Vec2 = (RotateTowards - Obj2Move->getWorldPosition()).normalize();

	float Angle = Unigine::Math::getAngle(Vec1, Vec2, Unigine::Math::vec3_up);
	Obj2Move->rotate(-Obj2Move->getWorldRotation().x, -Obj2Move->getWorldRotation().y, Angle * RoatateSpeed);
}

void ShooterAI::MoveTowards(Unigine::Math::Vec3 RotateTowards, Unigine::NodePtr Obj2Move, int Speed) {

	Unigine::Math::Vec3 Pos = Unigine::Math::lerp(
		Obj2Move->getWorldPosition(),
		RotateTowards,
		Unigine::Game::getIFps() * Speed /
		Unigine::Math::distance(Obj2Move->getWorldPosition(), RotateTowards));
	Obj2Move->setWorldPosition(Pos);
}

void ShooterAI::Shoot() {

	Unigine::NodePtr _Bullet = Unigine::World::loadNode(BulletPrefab.get());
	_Bullet->setWorldPosition(node->getChild(0)->getWorldPosition());
	_Bullet->worldLookAt(node->getWorldPosition() + node->getWorldDirection(Unigine::Math::AXIS_Y));

	Bullet* bullet = getComponent<Bullet>(_Bullet);
	bullet->setDamage(1);

	Unigine::BodyRigidPtr _BulletPhysics = _Bullet->getObjectBodyRigid();
	_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * 50);
}