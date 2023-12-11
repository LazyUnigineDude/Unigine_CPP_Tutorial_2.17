#include "HealthBar.h"

REGISTER_COMPONENT(HealthBar)

void HealthBar::Init() { health = Health.get(); }
void HealthBar::Init(int Health) { health = Health; }
int HealthBar::GetHealth() { return health; }
void HealthBar::HealthChange(int amount) { health += amount; }
