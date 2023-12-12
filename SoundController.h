#pragma once
#include <Unigine.h>

class SoundController : public Unigine::ComponentBase {

public:
	COMPONENT_DEFINE(SoundController, ComponentBase)

		PROP_PARAM(File, SoundFile);
	void Init();

	void PlaySound();
	void StopSound();
	bool isPlaying() { return Source->isPlaying(); }

private:
	Unigine::SoundSourcePtr Source;
};

inline int GetRand(int Num) { return std::rand() % Num; }