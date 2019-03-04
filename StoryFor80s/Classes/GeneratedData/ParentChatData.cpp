/*
This file (ParentChatData.cpp) is generated
*/
#include "ParentChatData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ParentChatData*>* ParentChatData::p_sharedDictionary = nullptr;

string ParentChatData::getId() const
{
	return to_string(p_chatId);
}

string ParentChatData::getChatId() const
{
	return p_chatId;
}

string ParentChatData::getName() const
{
	string localId = "parentChat_name_" + to_string(p_chatId);
	return LocalizationHelper::getLocalization(localId);
}

string ParentChatData::description() const
{
	string desc = "parentChatData = {\n";
	desc += "\tchatId : " + to_string(p_chatId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ParentChatData*>* ParentChatData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ParentChatData*>();
		static string resPath = "res/base/data/parentChat.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ParentChatData* parentChatData = new ParentChatData();
				parentChatData->p_chatId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ParentChatData*>(parentChatData->p_chatId, parentChatData));
			}
		}
	}
	return p_sharedDictionary;
}

ParentChatData* ParentChatData::getParentChatDataById(const string& chatId)
{
	if (ParentChatData::getSharedDictionary()->count(chatId)) {
		return ParentChatData::getSharedDictionary()->at(chatId);
	}
	return nullptr;
}

string ParentChatData::getFieldValue(const string & fieldName)
{
	if (fieldName == "chatId") {
		return to_string(this->getChatId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	}
	CCLOGWARN("Couldn't recognize %s in ParentChatData", fieldName.c_str());
	return "";
}

BaseData* ParentChatData::getDataByField(const string & fieldName)
{
	CCLOGWARN("Couldn't recognize %s in ParentChatData", fieldName.c_str());
	return nullptr;
}

