#include "SoundController.h"
REGISTER_COMPONENT(SoundController)

void SoundController::Init() {

	Source = Unigine::checked_ptr_cast<Unigine::SoundSource>(node);
	Source->setSampleName(SoundFile);
}

void SoundController::PlaySound() { Source->play(); Source->setPitch((GetRand(100) * 0.01) + 1); }
void SoundController::StopSound() { Source->stop(); }