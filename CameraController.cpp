#include "CameraController.h"

REGISTER_COMPONENT(CameraController)


void CameraController::Init() {

	MainCamera = Unigine::Game::getPlayer();

	if (Is_Inverted_Y.get())
	{
		Invert_Y = 1;
	}
	else Invert_Y = -1;

	if (Is_Inverted_X.get())
	{
		Invert_X = 1;
	}
	else Invert_X = -1;
}

void CameraController::Update() {


	MousePosition = Unigine::Input::getMouseCoordDelta();

	Angle += Invert_X * MousePosition.x * Unigine::Game::getIFps() * Rotation_Speed_Horizontal.get();

	Height = Unigine::Math::clamp(
		Height += Invert_Y * MousePosition.y * Unigine::Game::getIFps() * Rotation_Speed_Vertical.get(),
		Min_Max_Height.get().x,
		Min_Max_Height.get().y
	);

	NPoint.x = Radius.get() * Unigine::Math::cos(Angle);
	NPoint.y = Radius.get() * Unigine::Math::sin(Angle);
	NPoint.z = Height;

	NPoint += LookAtObj.get()->getWorldPosition();

	MainCamera->setWorldPosition(NPoint);
	MainCamera->worldLookAt(LookAtObj.get()->getWorldPosition());

}