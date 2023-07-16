#include "CharacterController.h"
REGISTER_COMPONENT(CharacterController)


void CharacterController::Init() {

	Animation = getComponent<ShooterAnim>(AnimationNode);
	Physics = getComponent<PhysicsController>(PhysicsNode);
	Health = getComponent<HealthBar>(HealthBarNode);
	Inventory = getComponent<InventoryController>(InventoryNode);

	//Unigine::EngineWindowPtr window = Unigine::WindowManager::getMainWindow();
	//window->setSize(Unigine::Math::ivec2(900, 400));
	//window->setPosition(Unigine::Math::ivec2(100, 100));

	Animation->Init(node);
	Physics->Init(node);
	Inventory->Init(Unigine::Game::getPlayer(), node);
}

void CharacterController::Update() {

	Inventory->Update();
	Animation->Update(Unigine::Game::getIFps(), Unigine::Game::getTime());

	if (!OpenUI) {
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SPACE)) { Animation->ChangeAnim(Animation->RUN); }
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) { Animation->ChangeAnim(Animation->WALK); }
		else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) { Animation->ChangeAnim(Animation->REVERSE_WALK); }
		else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) { Animation->ChangeAnim(Animation->SIDEWALK_L); }
		else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) { Animation->ChangeAnim(Animation->SIDEWALK_R); }
		else Animation->ChangeAnim(Animation->IDLE);
	}
	
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_Q)) { OpenUI = (OpenUI) ? 0 : 1; ShowInventory(OpenUI); }
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_E)) { Inventory->Interact(); }
}

void CharacterController::UpdatePhysics() {

	if(!OpenUI){
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SPACE)) { Physics->Run(true); }
	else Physics->Run(false);

	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) { Physics->Move(Physics->FORWARD); }
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) { Physics->Move(Physics->REVERSE); }
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) { Physics->Move(Physics->LEFT); }
	if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) { Physics->Move(Physics->RIGHT); }
	
	Physics->AutoRotate(Unigine::Game::getPlayer());
	}
}

void CharacterController::ShutDown() {
	Inventory->Shutdown();
}

void CharacterController::ShowInventory(bool isOpen) { (isOpen) ? Inventory->Show() : Inventory->Hide(); }
