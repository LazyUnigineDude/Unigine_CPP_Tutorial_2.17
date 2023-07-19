#include "Bullet.h"
#include "HealthBar.h"

REGISTER_COMPONENT(Bullet)

void Bullet::OnEnter(Unigine::BodyPtr Body, int num) {
	// Delete first, then interaction
	node->deleteLater();
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
			Health->HealthChange(Damage);
			Unigine::Log::message("Dropped health %d\n", Health->GetHealth());
		}
	}
	else {
		// Collision
		//Unigine::Log::message("Collision: %s %d\n", Body->getContactObject(num)->getName(), num);
		HealthBar* Health = getComponent<HealthBar>(Body->getContactObject(num));
		if (Health) {
			Health->HealthChange(Damage * 2);
			Unigine::Log::message("Dropped health %d\n", Health->GetHealth());
		}
	}
}

void Bullet::Init() { 
	StartTime = Unigine::Game::getTime(); 
	Body = node->getObjectBodyRigid();
	Body->addContactEnterCallback(Unigine::MakeCallback(this,&Bullet::OnEnter));
}

void Bullet::Update() {
	if (Unigine::Game::getTime() - StartTime > LifeTime) node->deleteLater();
}
