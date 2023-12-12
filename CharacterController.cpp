#include "CharacterController.h"
REGISTER_COMPONENT(CharacterController)

void CharacterController::Init() {

	Animation = getComponent<ShooterAnim>(AnimationNode);
	Physics = getComponent<PhysicsController>(PhysicsNode);
	Health = getComponent<HealthBar>(HealthBarNode);
	Inventory = getComponent<InventoryController>(InventoryNode);
	Interact = getComponent<Interactor>(DetectionNode);
	Gun = getComponent<GunHandler>(GunNode);
	Sound = getComponent<SoundController>(FootStepNode);

	//Unigine::EngineWindowPtr window = Unigine::WindowManager::getMainWindow();
	//window->setSize(Unigine::Math::ivec2(900, 400));
	//window->setPosition(Unigine::Math::ivec2(100, 100));

	Animation->Init(ObjectSkin);
	Physics->Init(node);
	Health->Init();
	Inventory->Init(Unigine::Game::getPlayer(), node);
	Interact->Init(Unigine::Game::getPlayer());
	Gun->Init(Unigine::Game::getPlayer());
	Sound->Init();

	HUD = HUD->MainHUD();

	Camera = getComponent<CameraFollower>(Unigine::Game::getPlayer());
}

void CharacterController::Update() {

	Interact->Update();
	Animation->Update(Unigine::Game::getIFps(), Unigine::Game::getTime());

	if (Animation->IsIdle()) { Sound->StopSound(); }
	else Sound->PlaySound();

	if (!OpenUI) {
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W) && Unigine::Input::isKeyPressed(Unigine::Input::KEY_SPACE)) { Animation->ChangeAnim(Animation->RUN); }
		if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_W)) { Animation->ChangeAnim(Animation->WALK); }
		else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_S)) { Animation->ChangeAnim(Animation->REVERSE_WALK); }
		else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_A)) { Animation->ChangeAnim(Animation->SIDEWALK_L); }
		else if (Unigine::Input::isKeyPressed(Unigine::Input::KEY_D)) { Animation->ChangeAnim(Animation->SIDEWALK_R); }
		else Animation->ChangeAnim(Animation->IDLE);
	}
	
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_TAB)) { OpenUI = (OpenUI) ? 0 : 1; ShowInventory(OpenUI); }
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_E)) { 

		Unigine::Math::ivec2 Item = Interact->GetItemFromDetection();
		DatabaseController* Db = Db->GetDatabase();

		if (Item.x && Db->GetItemType(Item.x) == Db->WEAPON) Gun->GrabGun(Item);
		else Inventory->AddToInventory(Item);
	}

	if (Gun->IsHolding()) {
		if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_LEFT)) { Gun->Shoot(Unigine::Game::getTime()); HUD->UpdateGun(Gun->GetGUIValues()); }
		if (Unigine::Input::isMouseButtonDown(Unigine::Input::MOUSE_BUTTON_RIGHT)) { ChangeState(Animation->AIMED); Camera->SetState(Camera->Aiming); }
		if (Unigine::Input::isMouseButtonUp(Unigine::Input::MOUSE_BUTTON_RIGHT)) { ChangeState(Animation->EQUIPPED);  Camera->SetState(Camera->Normal); }
		if (Unigine::Input::isKeyDown(Unigine::Input::KEY_R)) { Gun->Reload();	HUD->UpdateGun(Gun->GetGUIValues()); }
	}
	if ((Unigine::Input::isKeyDown(Unigine::Input::KEY_Q))) {
		if (!Gun->IsGrabbed()) { Unigine::Log::message("Find a Gun first!\n"); ChangeState(Animation->NORMAL); Camera->SetState(Camera->Normal); }
		else if (Gun->IsGrabbed() && Gun->IsHolding()) { ChangeState(Animation->NORMAL);  Camera->SetState(Camera->Normal); }
			else ChangeState(Animation->EQUIPPED);
	}
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
void CharacterController::ChangeState(ShooterAnim::SHOOTER_STATE State) {

	switch (State) {
	case ShooterAnim::NORMAL:
		Animation->ChangeState(Animation->NORMAL);
		if (Gun->IsHolding()) { 
			Gun->UnEquip();
			HUD->HideGun();
		}
		break;
	case ShooterAnim::EQUIPPED:
		if (!Gun->IsHolding()) { Gun->Equip(); }
		if (Gun->IsGrabbed()) { Animation->ChangeState(Animation->EQUIPPED); HUD->UpdateGun(Gun->GetGUIValues()); }
		break;
	case ShooterAnim::AIMED:
		if (Gun->IsHolding()) {
			Animation->ChangeState(Animation->AIMED);
		}
		break;
	default: break; }
}
