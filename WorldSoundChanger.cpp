#include "WorldSoundChanger.h"
REGISTER_COMPONENT(WorldSoundChanger);

void WorldSoundChanger::Init() {

	Trigger = Unigine::checked_ptr_cast<Unigine::WorldTrigger>(node);
	Trigger->addEnterCallback(Unigine::MakeCallback(this, &WorldSoundChanger::StartSong));
}

void WorldSoundChanger::StartSong(Unigine::NodePtr Node) {

	Source = Unigine::checked_ptr_cast<Unigine::SoundSource>(Node);

	std::string one, two;
	one = Source->getSampleName();
	two = SoundFile.get();

	if (one != two) {
		Source->setSampleName(SoundFile);
		Source->play();
	}
}