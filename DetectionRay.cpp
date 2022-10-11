#include "DetectionRay.h"
#include "GunHandler.h"

REGISTER_COMPONENT(DetectionRay)

void DetectionRay::Init(){

	RayPtr = Unigine::WorldIntersection::create();
	Equip = node.get()->getChild(0)->getChild(0)->getChild(0)->getChild(0);
}


void DetectionRay::Update() {

	Unigine::ObjectPtr IObj = Unigine::World::getIntersection(
		CameraNode.get()->getWorldPosition(),
		CameraNode.get()->getWorldPosition() + (CameraNode.get()->getWorldDirection() * 100),
		0x00000002,
		RayPtr
	);

	if (IObj) {
		Unigine::Visualizer::renderPoint3D(RayPtr.get()->getPoint(), 0.1f, Unigine::Math::vec4_red);

		if (Unigine::Input::isKeyDown(Unigine::Input::KEY_E)) {
		
			// Equip
			//Unigine::Console::message("Picked Up"); //Works
			Equip.get()->addChild(IObj);
			//Equip.get()->getChild(0)->setPosition(Unigine::Math::vec3_zero); // Works Too
			IObj.get()->setPosition(Unigine::Math::vec3_zero);

			// Change state to equipped
			ShooterAnim* _temp = getComponent<ShooterAnim>(node->getChild(0)->getChild(0));
			_temp->ChangeState(_temp->EQUIPPED);
			GunHandler* _gun = getComponent<GunHandler>(node->getChild(1));
			_gun->GetGun(IObj);
		}
	}
}