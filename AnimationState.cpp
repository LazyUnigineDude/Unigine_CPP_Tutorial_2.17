#include "AnimationState.h"

REGISTER_COMPONENT(AnimationState)

void AnimationState::ResetWeight() { isWeightChanged = true; if (isWeightChanged) { Weight = 0; isWeightChanged = false; } }

void AnimationState::ChangeState() {
	
	switch (MainState)
	{

	case AnimationState::IDLE:
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT)) 
					{ ResetWeight(); MainState = ANIMSTATES::RUN; PrevState = ANIMSTATES::IDLE;}
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) 
					{ ResetWeight(); MainState = ANIMSTATES::WALK; PrevState = ANIMSTATES::IDLE; }
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S))
					{ ResetWeight(); MainState = ANIMSTATES::REVERSE_WALK; PrevState = ANIMSTATES::IDLE; }
		MainCharacter->lerpLayer(ANIMSTATES::PROCEDURAL, PrevState,ANIMSTATES::IDLE, Weight * 2);
		break;
	case AnimationState::WALK:
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT)) 
					{ ResetWeight(); MainState = ANIMSTATES::RUN; PrevState = ANIMSTATES::WALK; }
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_W)) 
					{ ResetWeight(); MainState = ANIMSTATES::IDLE; PrevState = ANIMSTATES::WALK; }
		MainCharacter->lerpLayer(ANIMSTATES::PROCEDURAL, PrevState, ANIMSTATES::WALK, Weight * 1.7f);
		break;
	case AnimationState::REVERSE_WALK:
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_S)) 
					{ ResetWeight(); MainState = ANIMSTATES::IDLE; PrevState = ANIMSTATES::REVERSE_WALK; }
		MainCharacter->lerpLayer(ANIMSTATES::PROCEDURAL, PrevState, ANIMSTATES::REVERSE_WALK, Weight * 1.65f);
		break;
	case AnimationState::RUN:
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_SHIFT)) 
					{ ResetWeight(); MainState = ANIMSTATES::WALK; PrevState = ANIMSTATES::RUN; }
		if (Unigine::Input::isKeyUp(Unigine::Input::KEY_W)) 
					{ ResetWeight(); MainState = ANIMSTATES::IDLE; PrevState = ANIMSTATES::RUN; }
		MainCharacter->lerpLayer(ANIMSTATES::PROCEDURAL, PrevState, ANIMSTATES::RUN, Weight * 3);
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

	MainCharacter->setNumLayers(ANIMSTATES::COUNT);

	int IdleNum = MainCharacter->addAnimation(Idle);
	int WalkNum = MainCharacter->addAnimation(Walk);
	int R_WalkNum = MainCharacter->addAnimation(RWalk);
	int RunNum  = MainCharacter->addAnimation(Run);

	MainCharacter->setAnimation(ANIMSTATES::PROCEDURAL, IdleNum); // Procedural
	MainCharacter->setAnimation(ANIMSTATES::IDLE, IdleNum);
	MainCharacter->setAnimation(ANIMSTATES::WALK, WalkNum);
	MainCharacter->setAnimation(ANIMSTATES::REVERSE_WALK, R_WalkNum);
	MainCharacter->setAnimation(ANIMSTATES::RUN, RunNum);
}


void AnimationState::Update() {

	MainCharacter->setFrame(ANIMSTATES::PROCEDURAL, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIMSTATES::IDLE, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIMSTATES::WALK, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIMSTATES::REVERSE_WALK, Unigine::Game::getTime() * 30);
	MainCharacter->setFrame(ANIMSTATES::RUN, Unigine::Game::getTime() * 30);
	
	Weight = Unigine::Math::clamp(Weight + Unigine::Game::getIFps(), 0.0f, 1.0f);
	
	ChangeState();
	//Unigine::Console::message("Weight is: %f \n", Weight);

	/*
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SHIFT)) { MainState = ANIMSTATES::RUN; }
	else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) { MainState = ANIMSTATES::WALK; }

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) { MainState = ANIMSTATES::REVERSE_WALK; }
	

	ChangeState();
	
	/*
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_V)) { Weight = Unigine::Math::clamp(Weight + Unigine::Game::getIFps(), 0.0f, 1.0f); }
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_C)) { Weight = Unigine::Math::clamp(Weight - Unigine::Game::getIFps(), 0.0f, 1.0f); }

	MainCharacter->lerpLayer(0,1,2,Weight);
	
	Unigine::Console::message("Weight is: %f \n", Weight);*/
	
}