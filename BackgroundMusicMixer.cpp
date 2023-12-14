#include "BackgroundMusicMixer.h"
REGISTER_COMPONENT(BackgroundMusicMixer)

void BackgroundMusicMixer::Init() {

	Part1 = Unigine::static_ptr_cast<Unigine::SoundSource>(Sound1.get());
	Part2 = Unigine::static_ptr_cast<Unigine::SoundSource>(Sound2.get());

	MaxVol1 = Part1->getGain();
	MaxVol2 = Part2->getGain();

	Part1->setGain(MaxVol1 * 0.6f);
	Part2->setGain(0);

	for (int i = 0; i < TurretNodes.size(); i++) Turrets.push_back(getComponent<TurretClass>(TurretNodes[i]));
	
}

void BackgroundMusicMixer::Update() {

	for (auto &i : Turrets) {

		if (i->isAttacking()) {

			Part1->setGain(Unigine::Math::clamp(Part1->getGain() + Unigine::Game::getIFps(), MaxVol1 * 0.6f, MaxVol1));
			Part2->setGain(Unigine::Math::clamp(Part2->getGain() + Unigine::Game::getIFps(), 0.0f, MaxVol2));
		}

		else {
			Part1->setGain(Unigine::Math::clamp(Part1->getGain() - Unigine::Game::getIFps(), MaxVol1 * 0.6f, MaxVol1));
			Part2->setGain(Unigine::Math::clamp(Part2->getGain() - Unigine::Game::getIFps(), 0.0f, MaxVol2));
		}
	}

}

void BackgroundMusicMixer::Shutdown() {}