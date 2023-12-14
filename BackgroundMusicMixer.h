#pragma once
#include <Unigine.h>
#include "TurretClass.h"

class BackgroundMusicMixer : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(BackgroundMusicMixer, ComponentBase)
		COMPONENT_INIT(Init, -1)
		COMPONENT_UPDATE(Update)
		COMPONENT_SHUTDOWN(Shutdown)
		PROP_PARAM(Node, Sound1)
		PROP_PARAM(Node, Sound2)
		PROP_ARRAY(Node, TurretNodes)

protected:
	void Init(), Update(), Shutdown();

private:
	float MaxVol1 = 0, MaxVol2 = 0, MinVol1, MinVol2;
	Unigine::SoundSourcePtr Part1, Part2;
	Unigine::Vector<TurretClass*> Turrets;
};

