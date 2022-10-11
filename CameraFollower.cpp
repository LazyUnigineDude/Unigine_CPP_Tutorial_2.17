#include "CameraFollower.h"
REGISTER_COMPONENT(CameraFollower)

void CameraFollower::Init() { 

	Parameter = node->getProperty(1)->getParameterPtr();
	MainCamera = Parameter->getChild(0)->getValueNode();
	ObjectFollow = Parameter->getChild(1)->getValueNode();
	InvertCheck();
	SetState(CAMERASTATE::Normal);
}

void CameraFollower::InvertCheck() {

	if (Parameter->getChild(2)->getValueToggle()) HorInv = 1; else HorInv = -1;
	if (Parameter->getChild(3)->getValueToggle()) VerInv = -1; else VerInv = 1;
}

void CameraFollower::SetState(CAMERASTATE STATE) {
	if (this->STATE != STATE) {
		Weight = 0;
		PREV_STATE = this->STATE;
		this->STATE = STATE;
	}
}

void CameraFollower::Update() {
	
	if (isAiming) { SetState(CAMERASTATE::Aiming); }
	else SetState(CAMERASTATE::Normal);
	
	LerpLayer(STATE);
	UpdateCamera();
}

void CameraFollower::UpdateCamera() {

	Unigine::Math::ivec2 MousePos = Unigine::Input::getMouseDeltaPosition();
	
	Angle += HorInv * MousePos.x * Unigine::Game::getIFps() * RotSpeedH;

	Height = Unigine::Math::clamp(
		Height += VerInv * MousePos.y * Unigine::Game::getIFps() * RotSpeedV,
		MinHeight * Unigine::Math::Consts::DEG2RAD,
		MaxHeight * Unigine::Math::Consts::DEG2RAD
	);
	// Point to look at
	NPoint.x = Radius * Unigine::Math::cos(Angle);
	NPoint.y = Radius * Unigine::Math::sin(Angle);
	NPoint.z = HeightValue;
	NPoint += ObjectFollow->getWorldPosition();
	// Camera Point
	CPoint.x = (CamRadius + 2) * Unigine::Math::cos(Angle - 20);
	CPoint.y = (CamRadius + 2) * Unigine::Math::sin(Angle - 20);
	CPoint.z = Unigine::Math::tan(Height);
	CPoint += NPoint;

	MainCamera->setWorldPosition(CPoint);
	MainCamera->worldLookAt(NPoint);
}

void CameraFollower::LerpLayer(CAMERASTATE STATE) {

	Weight = Unigine::Math::clamp(Weight += Unigine::Game::getIFps() * Parameter->getChild(4)->getValueFloat(), 0.0f, 1.0f);

	switch (STATE) {
	case CameraFollower::Normal: LerpValues(Parameter->getChild(5)->getChild(1), Parameter->getChild(5)->getChild(0)); break;
	case CameraFollower::Aiming: LerpValues(Parameter->getChild(5)->getChild(0), Parameter->getChild(5)->getChild(1)); break;
	default:break;
	}
}

void CameraFollower::LerpValues(Unigine::PropertyParameterPtr PREV_STATE, Unigine::PropertyParameterPtr STATE) {

	Radius		= Unigine::Math::lerp(PREV_STATE->getChild(1)->getValueFloat(), STATE->getChild(1)->getValueFloat(), Weight);
	CamRadius	= Unigine::Math::lerp(PREV_STATE->getChild(2)->getValueFloat(), STATE->getChild(2)->getValueFloat(), Weight);
	HeightValue = Unigine::Math::lerp(PREV_STATE->getChild(3)->getValueFloat(), STATE->getChild(3)->getValueFloat(), Weight);
	RotSpeedH	= Unigine::Math::lerp(PREV_STATE->getChild(4)->getValueFloat(), STATE->getChild(4)->getValueFloat(), Weight);
	RotSpeedV	= Unigine::Math::lerp(PREV_STATE->getChild(5)->getValueFloat(), STATE->getChild(5)->getValueFloat(), Weight);
	MinHeight	= Unigine::Math::lerp(PREV_STATE->getChild(6)->getValueVec2().x, STATE->getChild(6)->getValueVec2().x, Weight);
	MaxHeight	= Unigine::Math::lerp(PREV_STATE->getChild(6)->getValueVec2().y, STATE->getChild(6)->getValueVec2().y, Weight);
}