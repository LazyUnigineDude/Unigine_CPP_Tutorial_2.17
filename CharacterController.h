#pragma once

#include <Unigine.h>


class CharacterController : public Unigine::ComponentBase
{

public:

	COMPONENT_DEFINE(CharacterController,ComponentBase)
		COMPONENT_INIT(Init)
		COMPONENT_UPDATE(Update)

protected:
	void Init();
	void Update();

private:




};

