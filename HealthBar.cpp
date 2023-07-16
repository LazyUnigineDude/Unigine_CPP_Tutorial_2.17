#include "HealthBar.h"

REGISTER_COMPONENT(HealthBar)

void HealthBar::Init() { health = Health.get(); }
int HealthBar::GetHealth() { return health; }
void HealthBar::HealthChange(int amount) { health += amount; }
