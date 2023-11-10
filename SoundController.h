#pragma once
#include <Unigine.h>

class SoundController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(SoundController, ComponentBase)
		COMPONENT_INIT(Init)

protected:
	void Init();

private:
	Unigine::SoundSourcePtr Source;
	Unigine::AmbientSourcePtr Ambience;
};

