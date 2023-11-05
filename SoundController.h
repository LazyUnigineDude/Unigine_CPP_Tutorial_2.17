#pragma once
#include <Unigine.h>

class SoundController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(SoundController, ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)
		COMPONENT_SHUTDOWN(Shutdown)

protected:
	void Init(), Update(), Shutdown();

private:
	Unigine::SoundSourcePtr Source;
	Unigine::AmbientSourcePtr Ambience;
};

