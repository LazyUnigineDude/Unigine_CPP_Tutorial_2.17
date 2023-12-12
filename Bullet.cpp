#include "Bullet.h"
#include "HealthBar.h"

REGISTER_COMPONENT(Bullet)

void Bullet::OnEnter(Unigine::BodyPtr Body, int num) {
	Unigine::BodyPtr
		Body1 = Body->getContactBody0(num),
		Body2 = Body->getContactBody1(num),
		CapturedBody = nullptr;

	if (Body1 && Body1 != Body) CapturedBody = Body1;
	if (Body2 && Body2 != Body) CapturedBody = Body2;

	if (CapturedBody) {
		// Body
		//Unigine::Log::message("Physics: %s %d\n",CapturedBody->getObject()->getName(), num);
		HealthBar* Health = getComponent<HealthBar>(CapturedBody->getObject());
		if (Health) {
			Health->HealthChange(-DamageAmount);
			Unigine::Log::message("Dropped health %d\n", Health->GetHealth());
		}
	}
	else {
		// Collision
		//Unigine::Log::message("Collision: %s %d\n", Body->getContactObject(num)->getName(), num);
		HealthBar* Health = getComponent<HealthBar>(Body->getContactObject(num));
		if (Health) {
			Health->HealthChange(-DamageAmount);
			Unigine::Log::message("Dropped health %d\n", Health->GetHealth());
		}
	}

	Body->removeContactEnterCallback(Callback);
	node->deleteLater();
}

void Bullet::Init() { 
	StartTime = Unigine::Game::getTime(); 
	Body = node->getObjectBodyRigid();
	Callback = Body->addContactEnterCallback(Unigine::MakeCallback(this,&Bullet::OnEnter));
}

void Bullet::Update() {
	if (Unigine::Game::getTime() - StartTime > LifeTime) node->deleteLater();
}
