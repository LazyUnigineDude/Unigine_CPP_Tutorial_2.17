#include "GunHandler.h"
REGISTER_COMPONENT(GunHandler)

void GunHandler::Update()
{
	if (isHolding)
	{
		if (Unigine::Input::isMouseButtonPressed(Unigine::Input::MOUSE_BUTTON_LEFT))
		{
			if (Unigine::Game::getTime() > RateofFireTime)
			{
				RateofFireTime = Unigine::Game::getTime() + (1 / RoF);
				Shoot(Unigine::Game::getPlayer()->getWorldPosition() + Unigine::Game::getPlayer()->getWorldDirection() * 100);
			}
		}
		if (Unigine::Input::isKeyDown(Unigine::Input::KEY_R)) {Reload(); }
	}
}

void GunHandler::GetGun(Unigine::ObjectPtr Gun) { 
	this->Gun = Gun; 
	isHolding = true;
	RoF = Gun->getProperty(0)->getParameterPtr(2)->getValueInt();
	CurrentBulletAmount = Gun->getProperty(0)->getParameterPtr(3)->getValueInt();
	ReloadAmount = Gun->getProperty(0)->getParameterPtr(4)->getValueInt();

	HUD = getComponent<HUDMaker>(GUNHUD);
	Reload();
}

void GunHandler::Shoot(Unigine::Math::vec3& Lookat) {
	if (AmountInGun > 0) {
	Unigine::NodePtr _Bullet = Unigine::World::loadNode(Gun->getProperty(0)->getParameterPtr(0)->getValueFile());
	_Bullet->setWorldPosition(Gun.get()->getChild(0)->getWorldPosition());
	_Bullet->worldLookAt(Lookat);

	Bullet* bullet = getComponent<Bullet>(_Bullet);
	bullet->setDamage(Gun->getProperty(0)->getParameterPtr(1)->getValueInt());

	Unigine::BodyRigidPtr _BulletPhysics = _Bullet->getObjectBodyRigid();
	_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * 100);
	AmountInGun--;
	HUD->UpdateGun(AmountInGun,CurrentBulletAmount);
	}
	else if (AmountInGun == 0) { Reload(); }
}

void GunHandler::Reload() {

	int reload = ReloadAmount - AmountInGun;

	if (CurrentBulletAmount == 0) { Unigine::Log::message("Empty\n"); }
	else if (CurrentBulletAmount > reload)
	{
		CurrentBulletAmount -= reload;
		AmountInGun += reload;
	}
	else if (CurrentBulletAmount < reload)
	{
		AmountInGun += CurrentBulletAmount;
		CurrentBulletAmount = 0;
	}
	HUD->UpdateGun(AmountInGun, CurrentBulletAmount);
}

//void ShooterAnim::GetGun(Unigine::ObjectPtr Gun) {
//
//	this->Gun = Gun;
//	BulletPrefab = Unigine::NodeReference::create(Gun.get()->getProperty(0).get()->getParameterPtr(0).get()->getValueFile());
//}
//
//void ShooterAnim::Shoot(Unigine::Math::vec3& Lookat) {
//
//	Unigine::NodePtr _Bullet = Unigine::World::loadNode(BulletPrefab.get()->getNodePath());
//	_Bullet->setWorldPosition(Gun.get()->getChild(0)->getWorldPosition());
//	_Bullet->worldLookAt(Lookat);
//
//	Unigine::BodyRigidPtr _BulletPhysics = _Bullet->getObjectBodyRigid();
//	_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * 50);
//}
//
//void ShooterAnim::Shoot2() {
//
//	Unigine::WorldIntersectionPtr RayPtr = Unigine::WorldIntersection::create();
//	Unigine::ObjectPtr IObj = Unigine::World::getIntersection(
//		Gun->getChild(0)->getWorldPosition(),
//		Unigine::Game::getPlayer()->getWorldPosition() + Unigine::Game::getPlayer()->getWorldDirection() * 100,
//		0x00000001,
//		RayPtr
//	);
//
//	Unigine::Visualizer::renderLine3D(
//		Gun->getChild(0)->getWorldPosition(),
//		Unigine::Game::getPlayer()->getWorldPosition() + Unigine::Game::getPlayer()->getWorldDirection() * 100,
//		Unigine::Math::vec4_red);
//
//	if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_LEFT)) {
//
//		// Through the Shotgun
//		Unigine::Visualizer::renderPoint3D(RayPtr->getPoint(), 0.1f, Unigine::Math::vec4_black, true, 3);
//
//		// Through Camera
//		Unigine::WorldIntersectionPtr RayPtr2 = Unigine::WorldIntersection::create();
//		Unigine::ObjectPtr IObj2 = Unigine::World::getIntersection(
//			Unigine::Game::getPlayer()->getWorldPosition(),
//			Unigine::Game::getPlayer()->getWorldPosition() + Unigine::Game::getPlayer()->getWorldDirection() * 100,
//			0x00000001,
//			RayPtr2
//		);
//		if (IObj2) Shoot(RayPtr2->getPoint());
//		else Shoot(Unigine::Game::getPlayer()->getWorldPosition() + Unigine::Game::getPlayer()->getWorldDirection() * 100);
//		Unigine::Visualizer::renderPoint3D(RayPtr2->getPoint(), 0.1f, Unigine::Math::vec4_green, true, 3);
//	}
//
//	//Unigine::Console::message("InsideShoot2\n");
//	//Unigine::Visualizer::renderLine3D(node->getWorldPosition(), , Unigine::Math::vec4_red);
//	//Unigine::Visualizer::renderLine3D(Gun->getChild(0)->getWorldPosition(), Unigine::Game::getPlayer()->getWorldPosition() + (Unigine::Game::getPlayer()->getWorldDirection() * 100), Unigine::Math::vec4_red);
//}
//
//void ShooterAnim::ShootShotgun() {
//
//	Unigine::Math::mat4 Frustum(Unigine::Math::perspective(40, 1.4f, 0.05, 4));
//	Unigine::Math::quat Rotation(node->getWorldRotation() * Unigine::Math::quat(90, 0, 0));
//	Unigine::Math::mat4 View(Rotation, Gun->getChild(0)->getWorldPosition());
//
//	Unigine::Visualizer::renderFrustum(Frustum, View, Unigine::Math::vec4_black);
//
//	if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_LEFT)) {
//
//		Unigine::Visualizer::renderFrustum(Frustum, View, Unigine::Math::vec4_green, 2);
//		ObjectsCaptured.clear();
//
//		Unigine::Math::WorldBoundFrustum bf(Frustum, Unigine::Math::inverse(View));
//
//		Unigine::World::getIntersection(bf, Unigine::Node::OBJECT_MESH_STATIC, ObjectsCaptured);
//
//		for (int i = 0; i < ObjectsCaptured.size(); i++)
//		{
//			Unigine::Log::message("%s \n", ObjectsCaptured[i]->getName());
//		}
//	}
//}
