#include "AnimationState.h"

REGISTER_COMPONENT(AnimationState)

void AnimationState::ResetWeight() { isWeightChanged = true; if (isWeightChanged) { Weight = 0; isWeightChanged = false; } }

void AnimationState::ChangeState() {
	
	switch (MainState)
	{

	case AnimationState::IDLE:
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_LEFT_SHIFT))
					{ ResetWeight(); MainState = ANIM_STATE::RUN; PrevState = ANIM_STATE::IDLE;}
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) 
					{ ResetWeight(); MainState = ANIM_STATE::WALK; PrevState = ANIM_STATE::IDLE; }
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S))
					{ ResetWeight(); MainState = ANIM_STATE::REVERSE_WALK; PrevState = ANIM_STATE::IDLE; }
		MainCharacter->lerpLayer(ANIM_STATE::PROCEDURAL, PrevState,ANIM_STATE::IDLE, Weight * 2);
		break;
	case AnimationState::WALK:
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_LEFT_SHIFT)) 
					{ ResetWeight(); MainState = ANIM_STATE::RUN; PrevState = ANIM_STATE::WALK; }
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_W)) 
					{ ResetWeight(); MainState = ANIM_STATE::IDLE; PrevState = ANIM_STATE::WALK; }
		MainCharacter->lerpLayer(ANIM_STATE::PROCEDURAL, PrevState, ANIM_STATE::WALK, Weight * 1.7f);
		break;
	case AnimationState::REVERSE_WALK:
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_S)) 
					{ ResetWeight(); MainState = ANIM_STATE::IDLE; PrevState = ANIM_STATE::REVERSE_WALK; }
		MainCharacter->lerpLayer(ANIM_STATE::PROCEDURAL, PrevState, ANIM_STATE::REVERSE_WALK, Weight * 1.65f);
		break;
	case AnimationState::RUN:
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_LEFT_SHIFT))
					{ ResetWeight(); MainState = ANIM_STATE::WALK; PrevState = ANIM_STATE::RUN; }
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_W)) 
					{ ResetWeight(); MainState = ANIM_STATE::IDLE; PrevState = ANIM_STATE::RUN; }
		MainCharacter->lerpLayer(ANIM_STATE::PROCEDURAL, PrevState, ANIM_STATE::RUN, Weight * 3);
		break;

	default:
		break;
	}

}


void AnimationState::Init() {


	const char* Idle = Unigine::FileSystem::getGUID(IdleAnim.getRaw()).getFileSystemString();
	const char* Walk = Unigine::FileSystem::getGUID(WalkAnim.getRaw()).getFileSystemString();
	const char* RWalk = Unigine::FileSystem::getGUID(R_WalkAnim.getRaw()).getFileSystemString();
	const char* Run  = Unigine::FileSystem::getGUID(RunAnim.getRaw()).getFileSystemString();

	MainCharacter = Unigine::checked_ptr_cast<Unigine::ObjectMeshSkinned>(node);

	MainCharacter->setNumLayers(ANIM_STATE::COUNT);

	int IdleNum = MainCharacter->addAnimation(Idle);
	int WalkNum = MainCharacter->addAnimation(Walk);
	int R_WalkNum = MainCharacter->addAnimation(RWalk);
	int RunNum  = MainCharacter->addAnimation(Run);

	MainCharacter->setAnimation(ANIM_STATE::PROCEDURAL, IdleNum); // Procedural
	MainCharacter->setAnimation(ANIM_STATE::IDLE, IdleNum);
	MainCharacter->setAnimation(ANIM_STATE::WALK, WalkNum);
	MainCharacter->setAnimation(ANIM_STATE::REVERSE_WALK, R_WalkNum);
	MainCharacter->setAnimation(ANIM_STATE::RUN, RunNum);
}


void AnimationState::Update() {

	MainCharacter->setFrame(ANIM_STATE::PROCEDURAL, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIM_STATE::IDLE, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIM_STATE::WALK, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIM_STATE::REVERSE_WALK, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIM_STATE::RUN, Unigine::Game::getTime() * 30);
	
	Weight = Unigine::Math::clamp(Weight + Unigine::Game::getIFps(), 0.0f, 1.0f);
	
	ChangeState();
	//Unigine::Console::message("Weight is: %f \n", Weight);

	/*
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT)) { MainState = ANIM_STATE::RUN; }
	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) { MainState = ANIM_STATE::WALK; }

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) { MainState = ANIM_STATE::REVERSE_WALK; }
	

	ChangeState();
	
	/*
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_V)) { Weight = Unigine::Math::clamp(Weight + Unigine::Game::getIFps(), 0.0f, 1.0f); }
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_C)) { Weight = Unigine::Math::clamp(Weight - Unigine::Game::getIFps(), 0.0f, 1.0f); }

	MainCharacter->lerpLayer(0,1,2,Weight);
	
	Unigine::Console::message("Weight is: %f \n", Weight);*/
	
}