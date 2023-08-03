#include "GunHandler.h"
REGISTER_COMPONENT(GunHandler)

void GunHandler::Init(Unigine::PlayerPtr Camera) {
	this->Camera = Camera;
}

void GunHandler::GrabGun(Unigine::Math::ivec2 GunValue) {

	DatabaseController* Database = Database->GetDatabase();
	GunProperty = Database->GetGunProperty(GunValue.x);
	Item = GunValue;
	isGrabbed = true;
}

void GunHandler::Equip() {
	
	DatabaseController* Database = Database->GetDatabase();
	Gun = Unigine::World::loadNode(Database->GetPrefabPath(Item.x));
	HandlePosition->addChild(Gun);
	Gun->setPosition(Unigine::Math::Vec3_zero);
	Gun->setRotation(Unigine::Math::quat_zero);

	isHolding = true;
	Reload();
}

void GunHandler::UnEquip() {
	Gun->deleteLater();
	Item.y += AmountInGun;
	isHolding = false;
}

void GunHandler::Shoot(float Time) {

	if (isHolding && Time > RateofFireTime) {
		RateofFireTime = Time + (1 / GunProperty.RoF);
		Shoot(Camera->getWorldPosition() + Unigine::Math::Vec3(Camera->getWorldDirection()) * 100);
	}
}

void GunHandler::Shoot(Unigine::Math::Vec3 Lookat) {

	if (AmountInGun > 0) {
	Unigine::NodePtr _Bullet = Unigine::World::loadNode(GunProperty.BulletPath);
	_Bullet->setWorldPosition(Gun->getWorldPosition());
	_Bullet->worldLookAt(Lookat);

	Bullet* bullet = getComponent<Bullet>(_Bullet);
	bullet->setDamage(GunProperty.Damage);

	Unigine::BodyRigidPtr _BulletPhysics = _Bullet->getObjectBodyRigid();
	_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * 100);
	AmountInGun--;
	}
	else if (AmountInGun == 0) { Reload(); }
}

void GunHandler::Reload() {

	int reload = GunProperty.Reload - AmountInGun;

	if (Item.y + AmountInGun == 0) { Unigine::Log::message("Empty\n"); }
	else if (Item.y >= reload) {
		Item.y -= reload;
		AmountInGun += reload;
	}
	else if (Item.y < reload) {
		AmountInGun += Item.y;
		Item.y = 0;
	}
}

Unigine::Math::ivec2 GunHandler::GetGUIValues() { return Unigine::Math::ivec2(AmountInGun, Item.y); }

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
