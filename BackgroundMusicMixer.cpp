#include "BackgroundMusicMixer.h"
REGISTER_COMPONENT(BackgroundMusicMixer)

void BackgroundMusicMixer::Init() {

	Part1 = Unigine::static_ptr_cast<Unigine::SoundSource>(Sound1.get());
	Part2 = Unigine::static_ptr_cast<Unigine::SoundSource>(Sound2.get());

	MinVol1 = Part1->getGain() * 0.6f;
	MinVol2 = 0.0001f;

	MaxVol1 = Part1->getGain();
	MaxVol2 = Part2->getGain();

	Part1->setGain(MinVol1);
	Part2->setGain(MinVol2);

	for (int i = 0; i < TurretNodes.size(); i++) Turrets.push_back(getComponent<TurretClass>(TurretNodes[i]));
	
}

void BackgroundMusicMixer::Update() {

	float CurVol1 = Part1->getGain(), CurVol2 = Part2->getGain();
	int AttackMode = 0;

	for (auto& i : Turrets)  if (i->isAttacking()) AttackMode++;

		if (AttackMode != 0) {
			CurVol1 = Unigine::Math::clamp(CurVol1 + Unigine::Game::getIFps(), MinVol1, MaxVol1);
			CurVol2 = Unigine::Math::clamp(CurVol2 + Unigine::Game::getIFps(), MinVol2, MaxVol2);
		}
		else {
			CurVol1 = Unigine::Math::clamp(CurVol1 - Unigine::Game::getIFps(), MinVol1, MaxVol1);
			CurVol2 = Unigine::Math::clamp(CurVol2 - Unigine::Game::getIFps(), MinVol2, MaxVol2);
		}


	Part1->setGain(CurVol1);
	Part2->setGain(CurVol2);
}

void BackgroundMusicMixer::Shutdown() {}