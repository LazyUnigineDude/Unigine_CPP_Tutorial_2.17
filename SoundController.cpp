#include "SoundController.h"
REGISTER_COMPONENT(SoundController)

void SoundController::Init() {

	Source = Unigine::checked_ptr_cast<Unigine::SoundSource>(node);
	Source->setSampleName(SoundFile);
}

void SoundController::PlaySound() { Source->play(); }
void SoundController::StopSound() { Source->stop(); }