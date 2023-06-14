#include "DatabaseController.h"
REGISTER_COMPONENT(DatabaseController);


void DatabaseController::Init() {

	Parameter = DatabaseNode->getProperty(0)->getParameterPtr(0);
	int ID = 1;
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
