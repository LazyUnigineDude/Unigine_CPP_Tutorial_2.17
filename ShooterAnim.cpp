#include "ShooterAnim.h"
REGISTER_COMPONENT(ShooterAnim)


void ShooterAnim::Init(Unigine::NodePtr MeshSkinnedObj) {

	MainCharacter = Unigine::checked_ptr_cast<Unigine::ObjectMeshSkinned>(MeshSkinnedObj);
	MainCharacter->setNumLayers(2);
	UpdateAnims();
}

void ShooterAnim::Update(float IFPS, float Time) {

	for (int i = 0; i < 2; i++) { MainCharacter->setFrame(i, Time * 30); }
	Weight = Unigine::Math::clamp(Weight + IFPS, 0.0f, 1.0f);
	LerpLayer();
}

void ShooterAnim::ChangeState(SHOOTER_STATE STATE) { 
	
	if (this->_STATE != STATE) {
		_PREVSTATE = this->_STATE;
		this->_STATE = _STATE; 
		Weight = 0;
		UpdateAnims();
	}
}
void ShooterAnim::ChangeAnim(ANIM_STATE STATE) { 
	
if (this->STATE != STATE) {
		PREVSTATE = this->STATE;
		this->STATE = STATE;
		Weight = 0;
		UpdateAnims();
	}
}

void ShooterAnim::UpdateAnims() {

	SetAnimation(_PREVSTATE, PREVSTATE, 0);
	SetAnimation(_STATE, STATE, 1);
}

const char* ShooterAnim::GetAnimation(SHOOTER_STATE S_STATE, ANIM_STATE A_STATE) {

	const char* Temp;

	switch (S_STATE) {
	case ShooterAnim::NORMAL:	Temp = ANIM_NORMAL[A_STATE]; break;
	case ShooterAnim::EQUIPPED: Temp = ANIM_EQUIP[A_STATE]; break;
	case ShooterAnim::AIMED:    Temp = ANIM_AIM[A_STATE]; break;
	default: break;
	}

	return Temp;
}

void ShooterAnim::SetAnimation(SHOOTER_STATE S_STATE, ANIM_STATE A_STATE, int Layer) {

	const char* Temp = GetAnimation(S_STATE, A_STATE);
	MainCharacter->setAnimation(Layer, MainCharacter->addAnimation(Temp));
}
