#include "ShooterAnim.h"
#include "CameraFollower.h"

REGISTER_COMPONENT(ShooterAnim)

void ShooterAnim::ResetWeight() { isWeightChanged = true; if (isWeightChanged) { Weight = 0; isWeightChanged = false; } }

void ShooterAnim::ChangeState(SHOOTER_STATE STATE) { if (State != STATE) { State = STATE; } }


void ShooterAnim::ShooterState() {

	switch (State)
	{
	case ShooterAnim::NORMAL:

		//if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_Q)) { State = SHOOTER_STATE::EQUIPPED; }
		// Equip from Inventory
		//ChangeStateToEquipped();

		ChangeState(ANIMSTATES::COUNT * SHOOTER_STATE::NORMAL);
		break;
	case ShooterAnim::EQUIPPED:
		
		if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_RIGHT)) {
			State = SHOOTER_STATE::AIMED;
			
			CameraFollower* x = getComponent<CameraFollower>(CameraFollowerNode);
			x->isAiming = true;
		}

		ChangeState(ANIMSTATES::COUNT * SHOOTER_STATE::EQUIPPED);
		break;
	case ShooterAnim::AIMED:
		
		if (Unigine::Input::isMouseButtonUp(Unigine::Input::MOUSE_BUTTON_RIGHT)) {
			State = SHOOTER_STATE::EQUIPPED;

			CameraFollower* x = getComponent<CameraFollower>(CameraFollowerNode);
			x->isAiming = false;
		}

		ChangeState(ANIMSTATES::COUNT * SHOOTER_STATE::AIMED);
		break;
	default:
		break;
	}
}

void ShooterAnim::ChangeState(int SHOOTERSTATE) {

	switch (MainState)
	{

	case ShooterAnim::IDLE:
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT))
		{
			ResetWeight(); MainState = ANIMSTATES::RUN; PrevState = ANIMSTATES::IDLE;
		}
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W))
		{
			ResetWeight(); MainState = ANIMSTATES::WALK; PrevState = ANIMSTATES::IDLE;
		}
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S))
		{
			ResetWeight(); MainState = ANIMSTATES::REVERSE_WALK; PrevState = ANIMSTATES::IDLE;
		}
		MainCharacter->lerpLayer(ANIMSTATES::IDLE, PrevState + SHOOTERSTATE, ANIMSTATES::IDLE + SHOOTERSTATE, Weight * 2);
		break;
	case ShooterAnim::WALK:
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT))
		{
			ResetWeight(); MainState = ANIMSTATES::RUN; PrevState = ANIMSTATES::WALK;
		}
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_W))
		{
			ResetWeight(); MainState = ANIMSTATES::IDLE; PrevState = ANIMSTATES::WALK;
		}
		MainCharacter->lerpLayer(ANIMSTATES::IDLE, PrevState + SHOOTERSTATE, ANIMSTATES::WALK + SHOOTERSTATE, Weight * 1.7f);
		break;
	case ShooterAnim::REVERSE_WALK:
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_S))
		{
			ResetWeight(); MainState = ANIMSTATES::IDLE; PrevState = ANIMSTATES::REVERSE_WALK;
		}
		MainCharacter->lerpLayer(ANIMSTATES::IDLE, PrevState + SHOOTERSTATE, ANIMSTATES::REVERSE_WALK + SHOOTERSTATE, Weight * 1.65f);
		break;
	case ShooterAnim::RUN:
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_SHIFT))
		{
			ResetWeight(); MainState = ANIMSTATES::WALK; PrevState = ANIMSTATES::RUN;
		}
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_W))
		{
			ResetWeight(); MainState = ANIMSTATES::IDLE; PrevState = ANIMSTATES::RUN;
		}
		MainCharacter->lerpLayer(ANIMSTATES::IDLE, PrevState + SHOOTERSTATE, ANIMSTATES::RUN + SHOOTERSTATE, Weight * 3);
		break;

	default:
		break;
	}
}


void ShooterAnim::Init() {

	MainCharacter = Unigine::checked_ptr_cast<Unigine::ObjectMeshSkinned>(node);
	MainCharacter->setNumLayers(ANIMSTATES::COUNT * SHOOTER_STATE::_COUNT);

	for (int i = 0; i < ANIMSTATES::COUNT; i++)
	{
		const char* Temp = Unigine::FileSystem::getGUID(ANIM_NORMAL[i].getRaw()).getFileSystemString();
		MainCharacter->setAnimation(i, MainCharacter->addAnimation(Temp));

		Temp = Unigine::FileSystem::getGUID(ANIM_EQUIP[i].getRaw()).getFileSystemString();
		MainCharacter->setAnimation(i + ANIMSTATES::COUNT, MainCharacter->addAnimation(Temp));

		Temp = Unigine::FileSystem::getGUID(ANIM_AIM[i].getRaw()).getFileSystemString();
		MainCharacter->setAnimation(i + (ANIMSTATES::COUNT  * 2), MainCharacter->addAnimation(Temp));

	}
}

void ShooterAnim::Update(){

	for (int i = 0; i < ANIMSTATES::COUNT; i++)
	{
		MainCharacter->setFrame(i + (State * ANIMSTATES::COUNT), Unigine::Game::getTime() * 30);
	}

	Weight = Unigine::Math::clamp(Weight + Unigine::Game::getIFps(), 0.0f, 1.0f);

	ShooterState();
}