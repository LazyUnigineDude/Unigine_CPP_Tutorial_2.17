#include "HUDMaker.h"
REGISTER_COMPONENT(HUDMaker)

void HUDMaker::Init(){
	GUI = Unigine::Gui::getCurrent();
	Canvas = Unigine::WidgetCanvas::create();
	Image = Unigine::WidgetSprite::create();
	Buttons = Unigine::WidgetLabel::create();
	MainCharacterHealth = getComponent<HealthBar>(MainCharacter.get());
	CurrentHealth = MainCharacterHealth->GetHealth();

	Width = GUI->getWidth();
	Height = GUI->getHeight();

	// TEXT
	//int x = Canvas->addText(1);
	//Canvas->setTextColor(x, Unigine::Math::vec4(1,1,1,0.5));
	//Canvas->setTextText(x, "SAMPLE_TEXT");
	//Canvas->setTextSize(x, 30);
	//Canvas->setTextPosition(x, Unigine::Math::vec2((Width / 2) - (Canvas->getTextWidth(x) / 2), (Height / 2) - (Canvas->getTextHeight(x) / 2)));

	// BOX
	int y = Canvas->addPolygon(0);
	Canvas->setPolygonColor(y, Unigine::Math::vec4(0, 0, 0, 0.5));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width * 0.25) - 200, Height - 120, 0));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width * 0.25) +  50, Height - 120, 0));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width * 0.25) +  50, Height - 70, 0));
	Canvas->addPolygonPoint(y, Unigine::Math::vec3((Width * 0.25) - 200, Height - 70, 0));

	// Crosshair
	int z = Image->addLayer();
	Unigine::ImagePtr _i = Unigine::Image::create(); _i->load(CrossHair.get());
	Image->setImage(_i);
	Image->setHeight(25);
	Image->setWidth(25);
	Image->setPosition((Width * 0.5) - (Image->getWidth() * 0.5), Height * 0.5 - (Image->getHeight() * 0.5));
	
	// HealthGrid
	Health = Unigine::WidgetGridBox::create(10,1,1);
	AddHealth(CurrentHealth);
	Health->setPosition((Width * 0.25) - 200, Height - 120);

	// GUN
	CurrentAmount = Unigine::WidgetLabel::create();
	MaxAmount = Unigine::WidgetLabel::create();

	// Buttons
	Buttons->setText("Press Esc to Open Menu\nPress TAB to Open/Close Inventory\nPress Q to Equip Gun\nPress R to Reload\nPress E to Pickup Highlighted Objects\nHold LShift to Run");
	Buttons->setPosition((Width * 0.1), 200);
	Buttons->setFontSize(21);
	Buttons->setFontOutline(2);


	GUI->addChild(Image, GUI->ALIGN_FIXED | GUI->ALIGN_OVERLAP);
	GUI->addChild(Canvas, GUI->ALIGN_EXPAND);
	GUI->addChild(CurrentAmount, GUI->ALIGN_FIXED | GUI->ALIGN_OVERLAP);
	GUI->addChild(MaxAmount, GUI->ALIGN_FIXED | GUI->ALIGN_OVERLAP);
	GUI->addChild(Health, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
	GUI->addChild(Buttons, GUI->ALIGN_EXPAND | GUI->ALIGN_OVERLAP);
}

void HUDMaker::Update() {

	if (CurrentHealth > MainCharacterHealth->GetHealth()) {
		//GUI = Unigine::Gui::getCurrent();
		LoseHealth(CurrentHealth - MainCharacterHealth->GetHealth());
		CurrentHealth = MainCharacterHealth->GetHealth();
	}
	if (CurrentHealth < MainCharacterHealth->GetHealth()) {
		AddHealth(MainCharacterHealth->GetHealth() - CurrentHealth);
		CurrentHealth = MainCharacterHealth->GetHealth();
	}
}

void HUDMaker::Shutdown()
{
	GUI = Unigine::Gui::getCurrent();
	if (GUI->isChild(Image)) { GUI->removeChild(Image); Image->deleteLater(); }
	if (GUI->isChild(Canvas)) { GUI->removeChild(Canvas); Canvas->deleteLater(); }
	if (GUI->isChild(CurrentAmount)) { GUI->removeChild(CurrentAmount); CurrentAmount->deleteLater(); }
	if (GUI->isChild(MaxAmount)) { GUI->removeChild(MaxAmount); MaxAmount->deleteLater(); }
	if (GUI->isChild(Health)) { LoseHealth(CurrentHealth); GUI->removeChild(Health); Health->deleteLater(); }
	if (GUI->isChild(Buttons)) { GUI->removeChild(Buttons); Buttons->deleteLater(); }
}

void HUDMaker::HideGun() { CurrentAmount->setText(" "); MaxAmount->setText(" "); }
void HUDMaker::UpdateGun(Unigine::Math::ivec2 GunValues) {

	std::string Amount = std::to_string(GunValues.x);
	CurrentAmount->setText(Amount.c_str());
	CurrentAmount->setFontSize(48);
	CurrentAmount->setPosition(Width - 160, 20);

	Amount = std::to_string(GunValues.y);
	MaxAmount->setText(Amount.c_str());
	MaxAmount->setFontSize(48);
	MaxAmount->setPosition(Width - 80, 20);
}

void HUDMaker::AddHealth(int Amount) {

	for (int i = 0; i < Amount; i++)
	{
		Unigine::ImagePtr _i = Unigine::Image::create(); _i->load(HealthImage.get());
		Unigine::WidgetSpritePtr Image = Unigine::WidgetSprite::create();
		Image->addLayer();
		Image->setImage(_i);
		Image->setHeight(24);
		Image->setWidth(24);
		Health->addChild(Image);
	}
}

void HUDMaker::LoseHealth(int Amount) {

	for (int i = 0; i < Amount; i++)
	{
		Unigine::WidgetPtr Widget = Health->getChild(0);
		Health->removeChild(Widget);
		Widget->deleteLater();
	}
}