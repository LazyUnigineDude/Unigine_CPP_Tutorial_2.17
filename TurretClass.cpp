#include "TurretClass.h"
REGISTER_COMPONENT(TurretClass)

void TurretClass::Init() {

	Health = getComponent<HealthBar>(node);
	Health->Init();


}

void TurretClass::Update() {

}

void TurretClass::Shutdown() {

}
