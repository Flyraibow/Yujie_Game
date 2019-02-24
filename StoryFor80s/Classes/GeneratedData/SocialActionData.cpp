/*
This file (SocialActionData.cpp) is generated
*/
#include "SocialActionData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, SocialActionData*>* SocialActionData::p_sharedDictionary = nullptr;

string SocialActionData::getId() const
{
	return to_string(p_socialActionId);
}

string SocialActionData::getSocialActionId() const
{
	return p_socialActionId;
}

string SocialActionData::getName() const
{
	string localId = "socialAction_name_" + to_string(p_socialActionId);
	return LocalizationHelper::getLocalization(localId);
}

string SocialActionData::description() const
{
	string desc = "socialActionData = {\n";
	desc += "\tsocialActionId : " + to_string(p_socialActionId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, SocialActionData*>* SocialActionData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SocialActionData*>();
		static string resPath = "res/base/data/socialAction.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SocialActionData* socialActionData = new SocialActionData();
				socialActionData->p_socialActionId = buffer->getString();
				p_sharedDictionary->insert(pair<string, SocialActionData*>(socialActionData->p_socialActionId, socialActionData));
			}
		}
	}
	return p_sharedDictionary;
}

SocialActionData* SocialActionData::getSocialActionDataById(const string& socialActionId)
{
	if (SocialActionData::getSharedDictionary()->count(socialActionId)) {
		return SocialActionData::getSharedDictionary()->at(socialActionId);
	}
	return nullptr;
}

string SocialActionData::getFieldValue(const string & fieldName)
{
	if (fieldName == "socialActionId") {
		return to_string(this->getSocialActionId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	}
	CCLOGWARN("Couldn't recognize %s in SocialActionData", fieldName.c_str());
	return "";
}

