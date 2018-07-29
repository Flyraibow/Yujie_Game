/*
This file (DialogData.cpp) is generated
*/
#include "DialogData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<string, DialogData*>* DialogData::p_sharedDictionary = nullptr;

string DialogData::getId() const
{
	return to_string(p_dialogId);
}

string DialogData::getDialogId() const
{
	return p_dialogId;
}

bool DialogData::getShowFullNames() const
{
	return p_showFullNames;
}

bool DialogData::getShowImage() const
{
	return p_showImage;
}

HeroData* DialogData::getHeroIdData() const
{
	return HeroData::getHeroDataById(p_heroIdId);
}

string DialogData::getHeroIdId() const
{
	return p_heroIdId;
}

string DialogData::getDialogContent() const
{
	string localId = "dialog_dialogContent_" + to_string(p_dialogId);
	return LocalizationHelper::getLocalization(localId);
}

string DialogData::description() const
{
	string desc = "dialogData = {\n";
	desc += "\tdialogId : " + to_string(p_dialogId) + "\n";
	desc += "\tshowFullNames : " + to_string(p_showFullNames) + "\n";
	desc += "\tshowImage : " + to_string(p_showImage) + "\n";
	desc += "\theroId : " + to_string(p_heroIdId) + "\n";
	desc += "\tdialogContent : " + getDialogContent() + "\n";
	desc += "}\n";
	return desc;
}

map<string, DialogData*>* DialogData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, DialogData*>();
		static string resPath = "res/base/data/dialog.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				DialogData* dialogData = new DialogData();
				dialogData->p_dialogId = buffer->getString();
				dialogData->p_showFullNames = buffer->getChar();
				dialogData->p_showImage = buffer->getChar();
				dialogData->p_heroIdId = buffer->getString();
				p_sharedDictionary->insert(pair<string, DialogData*>(dialogData->p_dialogId, dialogData));
			}
		}
	}
	return p_sharedDictionary;
}

DialogData* DialogData::getDialogDataById(const string& dialogId)
{
	if (DialogData::getSharedDictionary()->count(dialogId)) {
		return DialogData::getSharedDictionary()->at(dialogId);
	}
	return nullptr;
}

