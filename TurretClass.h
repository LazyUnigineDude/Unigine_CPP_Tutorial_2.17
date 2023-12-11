#pragma once
#include <Unigine.h>
#include "HealthBar.h"

class TurretClass : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(TurretClass, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		COMPONENT_SHUTDOWN(Shutdown)

protected:
	void Init(), Update(), Shutdown();

private:
	Unigine::Ptr<HealthBar> Health;
};

