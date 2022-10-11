#include "PropertyChecker.h"
REGISTER_COMPONENT(PropertyChecker)



void PropertyChecker::Init() {

	PropertyPtr = node->getProperty(0);
	ParameterPtr = PropertyPtr->getParameterPtr(0);


	Unigine::Log::message("HI, Name of Property %s \n", PropertyPtr->getName());
	Unigine::Log::message("Parameter Name: %s      ID NUM: %d",ParameterPtr->getName() , ParameterPtr->getValue().getInt() );
}