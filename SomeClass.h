#pragma once
#include <Unigine.h>

class SomeClass : public Unigine::ComponentBase {

public:

	COMPONENT_DEFINE(SomeClass, ComponentBase)
	COMPONENT_INIT(Init)
	COMPONENT_UPDATE(Update)
		PROP_PARAM(File, Image)

protected:

	void Init();
	void Update();

private:
	Unigine::WidgetButtonPtr Button;
	void x() {
			Button->setText("ON");
			Button->setButtonColor(Unigine::Math::vec4_green); }
	void y() {
			Button->setText("OFF"),
			Button->setButtonColor(Unigine::Math::vec4_white); }

	void CheckStatus() { (Button->isToggled()) ?  x() : y() ; }

};

