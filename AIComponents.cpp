#include "AIComponents.h"

 DetectionMaker::DetectionMaker(
	Unigine::NodePtr PhysicalTrigger, 
	Unigine::NodePtr MainObj,
	Unigine::NodePtr ViewPosition,
	int FieldDistance,
	int Mask) {

	DetectionArea = Unigine::static_ptr_cast<Unigine::PhysicalTrigger>(PhysicalTrigger);
	this->MainObj = MainObj;
	this->ViewPosition = ViewPosition;
	this->FieldDistance = FieldDistance;
	this->Mask = Mask;
	MainObjName = MainObj->getName();
}

 void DetectionMaker::AddCallbacks() { 
	 DetectionArea->addEnterCallback(Unigine::MakeCallback(this, &DetectionMaker::GetObjectsInArea));
 }

 void DetectionMaker::CalculateView() {

	Frustum = Unigine::Math::mat4(Unigine::Math::perspective(40, 1.4f, 0.05, FieldDistance));
	Rotation = Unigine::Math::quat(MainObj->getWorldRotation() * Unigine::Math::quat(90, 0, 0));
	View = Unigine::Math::Mat4(Rotation, ViewPosition->getWorldPosition());
}

void DetectionMaker::RenderView(bool isRender) {

	if (isRender) {
		Unigine::Visualizer::renderFrustum(Frustum, View, Unigine::Math::vec4_black);
		Unigine::Visualizer::renderVector(
			MainObj->getWorldPosition(),
			MainObj->getWorldPosition() + Unigine::Math::Vec3(MainObj->getWorldDirection(Unigine::Math::AXIS_Y)) * 2, 
			Unigine::Math::vec4_black);
		Unigine::Visualizer::renderSphere(DetectionArea->getSize().x, DetectionArea->getWorldTransform(), Unigine::Math::vec4_red);
	}
}

bool DetectionMaker::TargetVisibleInFrustum(Unigine::NodePtr Target, int Mask, const char* NameDetection) {

	FrustumBound = Unigine::Math::BoundFrustum(Frustum, Unigine::Math::inverse(Unigine::Math::mat4(View)));
	this->Mask = Mask;
	if (FrustumBound.inside(Unigine::Math::vec3(Target->getWorldPosition()))) {

		Unigine::ObjectPtr Obj = Unigine::World::getIntersection(
			MainObj->getWorldPosition(),
			Target->getWorldPosition(),
			Mask
		);
		if (Obj->getName() == NameDetection) return true;
	}
	return false;
}

void DetectionMaker::Dodge(bool isDodging, int DodgeDistance) { this->isDodging = isDodging; this->DodgeDistance = DodgeDistance; }

void DetectionMaker::GetObjectsInArea(Unigine::BodyPtr Body) {
	
	if (ObjectNameCheck(Body)) {
		Unigine::ObjectPtr ObjectAboutToHit = Unigine::World::getIntersection(
			Body->getPosition(),
			Body->getPosition() + Unigine::Math::Vec3(Body->getObject()->getBodyLinearVelocity()),
			Mask);

		if (ObjectNameCheck(ObjectAboutToHit) && isDodging == true) {
			
			Unigine::Math::Vec3 MainVector = Unigine::Math::Vec3(Body->getObject()->getBodyLinearVelocity()).normalize();
			float Angle = Unigine::Math::getAngle(
				Unigine::Math::vec3(MainObj->getWorldPosition()) + MainObj->getWorldDirection(),
				Unigine::Math::vec3(MainVector), Unigine::Math::vec3_up);

			(Angle > 0) ? Angle = 90.0f : Angle = -90.0f;

			Unigine::Math::Vec3 RotatedVector = Unigine::Math::Vec3(
				MainVector.x * Unigine::Math::cos(Angle) - MainVector.y * Unigine::Math::sin(Angle),
				MainVector.x * Unigine::Math::sin(Angle) + MainVector.y * Unigine::Math::cos(Angle),
				0).normalize();

			UpdateMainObj(RotatedVector * DodgeDistance);
		}
	}
}

bool DetectionMaker::ObjectNameCheck(Unigine::BodyPtr Body) { return (Body->getObject()->getName() != MainObjName) ? true : false; }
bool DetectionMaker::ObjectNameCheck(Unigine::ObjectPtr Body) { return (Body->getName() != MainObjName) ? true : false; }
void DetectionMaker::UpdateMainObj(Unigine::Math::Vec3 Position) { MainObj->setWorldPosition( MainObj->getWorldPosition() + Position); }

AIGunHandler::AIGunHandler(
	const char* BulletFilePath, 
	int damage,
	Unigine::NodePtr Target,
	Unigine::NodePtr Gun) {

	this->BulletFilePath = BulletFilePath;
	this->Damage = Damage;
	this->Target = Target;
	this->Gun = Gun;
}

void AIGunHandler::CalculatePositions() {

	FuturePoint = Target->getWorldPosition() + 
		Unigine::Math::Vec3(Target->getBodyLinearVelocity().normalize());
	FuturePoint.z = 1;
	FutureDistance = Unigine::Math::distance(
		Unigine::Math::vec3(Target->getWorldPosition()), Unigine::Math::vec3(FuturePoint));
	Distance = Unigine::Math::distance(
		Unigine::Math::vec3(Gun->getWorldPosition()), Unigine::Math::vec3(Target->getWorldPosition()));
}

void AIGunHandler::Shoot(double TargetSpeed) {

	Unigine::NodePtr _Bullet = Unigine::World::loadNode(BulletFilePath);
	_Bullet->setWorldPosition(Gun->getWorldPosition());

	/*Unigine::Ptr<Bullet> bullet = Unigine::static_ptr_cast<Bullet>(_Bullet);
	bullet->setDamage(Damage);*/
	Unigine::BodyRigidPtr _BulletPhysics = _Bullet->getObjectBodyRigid();

	if (TargetSpeed <= 1 && TargetSpeed > 0) {

		_Bullet->worldLookAt(Unigine::Math::lerp(Target->getWorldPosition(), FuturePoint, TargetSpeed / FutureDistance));
		_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * Distance);
	}
	else if (TargetSpeed > 1)
	{
		_Bullet->worldLookAt(FuturePoint);
		_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * Distance * (TargetSpeed / FutureDistance));
	}
	else
	{
		_Bullet->worldLookAt(Gun->getWorldPosition() + Unigine::Math::Vec3(Gun->getWorldDirection(Unigine::Math::AXIS_Y)));
		_BulletPhysics->addLinearImpulse(_Bullet->getWorldDirection(Unigine::Math::AXIS_Y) * Distance);
	}
	
}

void AIGunHandler::RenderVisuals(bool isRender, int Mask) {

	if (isRender) {
		Unigine::Visualizer::renderCapsule(
			0.5f, 
			1.5f, 
			Unigine::Math::dmat4(Target->getWorldRotation(), FuturePoint), 
			Unigine::Math::vec4_black, 
			Mask);
		Unigine::Visualizer::renderPoint3D(
			FuturePoint, 
			0.1f, 
			Unigine::Math::vec4_red, 
			false, 
			Mask);
	}
}
