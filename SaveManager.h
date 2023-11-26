#pragma once

#pragma once
#include <Unigine.h>
#include <stdlib.h>

struct SaveManager {

public:
	SaveManager() = default;
	SaveManager(Unigine::NodePtr ExclusionFile);
	~SaveManager();
	enum DATA { AUTOSAVE, SAVE1, SAVE2 };
	void Save(DATA Num);
	void Load(DATA Num);
	void LoadObjectsIntoWorld();
	bool FileExist(DATA Num);

private:
	void GetValueInsideSelector();
	Unigine::String Path = getenv("USERPROFILE"),
		Selector = "RunTimeFiles\\Selector.txt",
		SavePath1 = "CompanyName\\GameName\\AutoSave",
		SavePath2 = "CompanyName\\GameName\\SaveFile1",
		SavePath3 = "CompanyName\\GameName\\SaveFile2",
		LoadWorld = "EmptyWorld.world";
	Unigine::Vector<Unigine::NodePtr> Objects;
	Unigine::FilePtr File;
	Unigine::String SelectorString;
	Unigine::NodePtr ExclusionFile;
};

inline SaveManager::~SaveManager() { File->deleteLater(); Objects.clear(); }
inline SaveManager::SaveManager(Unigine::NodePtr ExclusionFile) {

	Path += "\\Documents\\";

	File = Unigine::File::create();
	this->ExclusionFile = ExclusionFile;

	if (File->open(Selector, "rb")) {
		File->close();
		GetValueInsideSelector();
	}
	else {
		//Unigine::Log::message("File Not Found, Creating...\n");
		File->open(Selector, "wb");
		File->writeString("0");
		File->close();
	}
}

inline void SaveManager::Save(DATA Data) {

	Unigine::Vector<Unigine::NodePtr>::iterator It;
	Unigine::World::getNodes(Objects);
	It = Objects.find(ExclusionFile);
	if (&It) Objects.remove(It);

	switch (Data) {
	case SaveManager::AUTOSAVE: Unigine::World::saveNodes(Path + SavePath1, Objects, 1); break;
	case SaveManager::SAVE1:	Unigine::World::saveNodes(Path + SavePath2, Objects, 1); break;
	case SaveManager::SAVE2:	Unigine::World::saveNodes(Path + SavePath3, Objects, 1); break;
	default: break;
	}
}

inline void SaveManager::Load(DATA Data) {

	File->open(Selector, "w");
	switch (Data) {
	case SaveManager::AUTOSAVE: File->writeString("0"); break;
	case SaveManager::SAVE1: 	File->writeString("1"); break;
	case SaveManager::SAVE2:	File->writeString("2"); break;
	default:break;
	}

	File->close();
	Unigine::World::loadWorld(LoadWorld);
}

inline bool SaveManager::FileExist(DATA Data) {

	bool isOpen = 0;
	switch (Data) {
	case SaveManager::AUTOSAVE: File->open(Path + SavePath1, "r"); isOpen = File->isOpened(); break;
	case SaveManager::SAVE1:    File->open(Path + SavePath2, "r"); isOpen = File->isOpened(); break;
	case SaveManager::SAVE2:    File->open(Path + SavePath3, "r"); isOpen = File->isOpened(); break;
	default: break;
	}
	if (isOpen) { File->close(); }
	return isOpen;
}

inline void SaveManager::GetValueInsideSelector() {

	File->open(Selector, "rb");
	SelectorString = File->readString();
	File->close();
}

inline void SaveManager::LoadObjectsIntoWorld() {

	GetValueInsideSelector();
	if (SelectorString == "0") Unigine::World::loadNodes(Path + SavePath1, Objects);
	if (SelectorString == "1") Unigine::World::loadNodes(Path + SavePath2, Objects);
	if (SelectorString == "2") Unigine::World::loadNodes(Path + SavePath3, Objects);
}