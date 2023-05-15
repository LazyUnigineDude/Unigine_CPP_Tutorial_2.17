#pragma once
#include <Unigine.h>

class FirstPerson {
	
	Unigine::Math::Vec3 NPoint;
	Unigine::NodePtr node;
	float Strafe, Height;

	void Add() {

		Unigine::Math::ivec2 MousePosition = Unigine::Input::getMouseDeltaPosition();
		Unigine::Math::vec3 CameraView, NodeView;

		// Setting Camera as root position of node
		Unigine::Math::Vec3 Pos = node->getWorldPosition() + Unigine::Math::Vec3(0, 0, 2.5);
		Unigine::Game::getPlayer()->setWorldPosition(Pos);

		Strafe += MousePosition.x * Unigine::Game::getIFps();
		Height += MousePosition.y * Unigine::Game::getIFps();

		// Create a point and rotate along node, then looktowards
		NPoint.x = Unigine::Math::cos(Strafe);
		NPoint.y = Unigine::Math::sin(Strafe);
		NPoint.z = Height;

		NPoint += Pos;
		Unigine::Game::getPlayer()->worldLookAt(NPoint);

		CameraView = Unigine::Game::getPlayer()->getWorldDirection();
		NodeView = node->getWorldDirection(Unigine::Math::AXIS_Y);

		float Angle = Unigine::Math::getAngle(
			CameraView,
			NodeView,
			node->getWorldDirection(Unigine::Math::AXIS_Z)
		);

		// Basic Rotate via Angular using angl;
		node->getObjectBodyRigid()->addAngularImpulse(node->getWorldDirection()* Angle* Unigine::Physics::getIFps() * 10);

		// Basic Rotate via Torque
		//node->getObjectBodyRigid()->addTorque(node->getWorldDirection() * Angle * Unigine::Physics::getIFps() * 100);
	}
};
