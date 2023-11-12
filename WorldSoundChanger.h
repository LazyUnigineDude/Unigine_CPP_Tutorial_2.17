#pragma once
#include <Unigine.h>
#include <string>

class WorldSoundChanger : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(WorldSoundChanger, ComponentBase)
		COMPONENT_INIT(Init);
		PROP_PARAM(File, SoundFile);
		PROP_PARAM(Node, ObjectDetect);

protected:
	void Init();

private:
	void StartSong(Unigine::NodePtr Node);
	Unigine::SoundSourcePtr Source;
	Unigine::WorldTriggerPtr Trigger;
};
