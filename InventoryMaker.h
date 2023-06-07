#pragma once
#include <Unigine.h>

struct InventoryMaker {

public:
	InventoryMaker() = default;
	InventoryMaker(Unigine::PropertyParameterPtr Parameter);
	bool Add(Unigine::Math::vec2& Item);
	bool Add(int& Position, Unigine::Math::vec2& Item);
	 Unigine::Math::vec2 Swap(int& Position, Unigine::Math::vec2& Item);
	 Unigine::Math::vec2 Delete(int& Position);

private:
	int ArrayAmount;
	Unigine::PropertyParameterPtr Parameter;
	Unigine::Math::vec2 GetItem(int& Position);
	bool SetItem(int& Position, Unigine::Math::vec2 Item);
};


inline InventoryMaker::InventoryMaker(
	Unigine::PropertyParameterPtr Parameter
) {
	ArrayAmount = Parameter->getArraySize();
	this->Parameter = Parameter; 
}

Unigine::Math::vec2 InventoryMaker::GetItem(
	int& Position
) {
	return Parameter->getChild(Position)->getValueVec2();
}

inline bool InventoryMaker::SetItem(
	int& Position, 
	Unigine::Math::vec2 Item
) {
	
	Parameter->getChild(Position)->setValueVec2(Item);
	return true;
}

bool InventoryMaker::Add(
	Unigine::Math::vec2& Item
) { 
	int Pos = 0; return Add(Pos, Item); 
}

bool InventoryMaker::Add(
	int& Position, 
	Unigine::Math::vec2& Item
) {

	if (Position > ArrayAmount) return false;

	Unigine::Math::vec2 _Item = GetItem(Position);
	
	if(_Item.x == 0) {
		return SetItem(Position, Item);
	}

	if (_Item.x == Item.x) {
		Unigine::Math::vec2 _New(Item.x, Item.y + _Item.y);
		return SetItem(Position, _New);
	}

	else {
		Position++;
		return Add(Position, Item);
	}
}

inline Unigine::Math::vec2 InventoryMaker::Swap(
	int& Position,
	Unigine::Math::vec2& Item
) {

	Unigine::Math::vec2 _Item = Delete(Position);
	SetItem(Position, Item);
	return _Item;
}

Unigine::Math::vec2 InventoryMaker::Delete(
	int& Position
) {
	Unigine::Math::vec2 _Item(GetItem(Position));
	SetItem(Position, Unigine::Math::vec2_zero);
	return _Item;
}