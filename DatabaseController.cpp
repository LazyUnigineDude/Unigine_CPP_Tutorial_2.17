#include "DatabaseController.h"
REGISTER_COMPONENT(DatabaseController);

void DatabaseController::Init()
{
	Parameter = DatabaseNode->getProperty(0)->getParameterPtr(0);
}

const char* DatabaseController::GetName(int& ID) 
{ 
	return Parameter->getChild(ID)->getChild(0)->getValueString();
}

int DatabaseController::GetValue(int& ID)
{
	return Parameter->getChild(ID)->getChild(1)->getValueInt();
}

const char* DatabaseController::GetImagePath(int& ID)
{
	return Parameter->getChild(ID)->getChild(2)->getValueString();
}

const char* DatabaseController::GetPrefabPath(int& ID)
{
	return Parameter->getChild(ID)->getChild(3)->getValueString();
}

DatabaseController::ITEM_TYPE DatabaseController::GetItemType(int& ID) {

	return ITEM_TYPE(Parameter->getChild(ID)->getChild(4)->getValueSwitch());
}


DatabaseController::GUNProps DatabaseController::GetGunProperty(int& ID)
{
	GUNProps Gun;

	Gun.BulletPath = Parameter->getChild(ID)->getChild(5)->getChild(0)->getValueFile();
	Gun.Damage	   = Parameter->getChild(ID)->getChild(5)->getChild(1)->getValueInt();
	Gun.RoF		   = Parameter->getChild(ID)->getChild(5)->getChild(2)->getValueFloat();
	Gun.Reload	   = Parameter->getChild(ID)->getChild(5)->getChild(3)->getValueInt();

	return Gun;
}
