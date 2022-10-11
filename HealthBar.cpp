#include "HealthBar.h"

REGISTER_COMPONENT(HealthBar)

void HealthBar::Check() { if (health <= 0) node->deleteLater(); }
void HealthBar::DropHealth(int amount) { health -= amount; Check(); }

void HealthBar::Init() {

	health = Health.get();
}