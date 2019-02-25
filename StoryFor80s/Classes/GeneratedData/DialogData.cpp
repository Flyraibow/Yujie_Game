/*
This file (DialogData.cpp) is generated
*/
#include "DialogData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, DialogData*>* DialogData::p_sharedDictionary = nullptr;

string DialogData::getId() const
{
	return to_string(p_dialogId);
}

string DialogData::getDialogId() const
{
	return p_dialogId;
}

FriendData* DialogData::getFriendData() const
{
	return FriendData::getFriendDataById(p_friendId);
}

string DialogData::getFriendId() const
{
	return p_friendId;
}

string DialogData::getName() const
{
	return p_name;
}

string DialogData::getContent() const
{
	string localId = "dialog_content_" + to_string(p_dialogId);
	return LocalizationHelper::getLocalization(localId);
}

vector<string> DialogData::getParameters() const
{
	return p_parameters;
}

string DialogData::description() const
{
	string desc = "dialogData = {\n";
	desc += "\tdialogId : " + to_string(p_dialogId) + "\n";
	desc += "\tfriend : " + to_string(p_friendId) + "\n";
	desc += "\tname : " + to_string(p_name) + "\n";
	desc += "\tcontent : " + getContent() + "\n";
	desc += "\tparameters : " + to_string(p_parameters) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, DialogData*>* DialogData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, DialogData*>();
		static string resPath = "res/base/data/dialog.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				DialogData* dialogData = new DialogData();
				dialogData->p_dialogId = buffer->getString();
				dialogData->p_friendId = buffer->getString();
				dialogData->p_name = buffer->getString();
				auto parametersCount = buffer->getLong();
				for (int j = 0; j < parametersCount; ++j) {
					dialogData->p_parameters.push_back(buffer->getString());
				}
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

string DialogData::getFieldValue(const string & fieldName)
{
	if (fieldName == "dialogId") {
		return to_string(this->getDialogId());
	} else if (fieldName == "friend") {
		return to_string(this->getFriendId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "content") {
		return to_string(this->getContent());
	} else if (fieldName == "parameters") {
		return to_string(this->getParameters());
	}
	CCLOGWARN("Couldn't recognize %s in DialogData", fieldName.c_str());
	return "";
}

