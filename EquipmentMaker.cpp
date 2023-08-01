#include "EquipmentMaker.h"
REGISTER_COMPONENT(EquipmentMaker)

void EquipmentMaker::Init() {

	Equipment = InventoryMaker(EquipmentNode->getProperty(0)->getParameterPtr(0));
}
