#pragma once
#include <Unigine.h>

struct InventoryMaker {

public:
	InventoryMaker() = default;
	InventoryMaker(Unigine::PropertyParameterPtr Parameter);
	bool Add(Unigine::Math::ivec2& Item);
	bool Add(int& Position, Unigine::Math::ivec2& Item);
	void Swap(int& Position1, int& Position2);
	Unigine::Math::ivec2 Swap(int& Position, Unigine::Math::ivec2& Item);
	Unigine::Math::ivec2 Delete(int& Position);
	int ArraySize() { return ArrayAmount; }
	Unigine::Math::ivec2 GetItem(int& Position);

private:
	int ArrayAmount;
	Unigine::PropertyParameterPtr Parameter;
	bool SetItem(int& Position, Unigine::Math::ivec2 Item);
};


inline InventoryMaker::InventoryMaker( Unigine::PropertyParameterPtr Parameter ) {
	ArrayAmount = Parameter->getArraySize();
	this->Parameter = Parameter; 
}

Unigine::Math::ivec2 InventoryMaker::GetItem( int& Position) { return Parameter->getChild(Position)->getValueIVec2(); }

inline bool InventoryMaker::SetItem( int& Position, Unigine::Math::ivec2 Item ) {
		Parameter->getChild(Position)->setValueIVec2(Item);
	return true;
}

bool InventoryMaker::Add( Unigine::Math::ivec2& Item) { int Pos = 0; return Add(Pos, Item); }
bool InventoryMaker::Add( int& Position, Unigine::Math::ivec2& Item) {
	if (Position > ArrayAmount) return false;

	Unigine::Math::ivec2 _Item = GetItem(Position);
	
	if(_Item.x == 0) {
		return SetItem(Position, Item);
	}

	if (_Item.x == Item.x) {
		Unigine::Math::ivec2 _New(Item.x, Item.y + _Item.y);
		return SetItem(Position, _New);
	}

	else {
		Position++;
		return Add(Position, Item);
	}
}

inline void InventoryMaker::Swap(int& Position1, int& Position2) {

	Unigine::Math::ivec2 _Item1 = Delete(Position1);
	if (GetItem(Position2).x == _Item1.x) { Add(Position2, _Item1); }
	else {
		Unigine::Math::ivec2 _Item2 = Delete(Position2);
		SetItem(Position1, _Item2);
		SetItem(Position2, _Item1);
	}
}

inline Unigine::Math::ivec2 InventoryMaker::Swap( int& Position, Unigine::Math::ivec2& Item ) {
	Unigine::Math::ivec2 _Item = Delete(Position);
	SetItem(Position, Item);
	return _Item;
}

Unigine::Math::ivec2 InventoryMaker::Delete( int& Position ) {
	Unigine::Math::ivec2 _Item(GetItem(Position));
	SetItem(Position, Unigine::Math::ivec2_zero);
	return _Item;
}