/*
This file (AbilityData.cpp) is generated
*/
#include "AbilityData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, AbilityData*>* AbilityData::p_sharedDictionary = nullptr;

string AbilityData::getId() const
{
	return to_string(p_abilityId);
}

int AbilityData::getAbilityId() const
{
	return p_abilityId;
}

string AbilityData::getAbilityName() const
{
	string localId = "ability_abilityName_" + to_string(p_abilityId);
	return LocalizationHelper::getLocalization(localId);
}

string AbilityData::getAbilityDescription() const
{
	string localId = "ability_abilityDescription_" + to_string(p_abilityId);
	return LocalizationHelper::getLocalization(localId);
}

string AbilityData::description() const
{
	string desc = "abilityData = {\n";
	desc += "\tabilityId : " + to_string(p_abilityId) + "\n";
	desc += "\tabilityName : " + getAbilityName() + "\n";
	desc += "\tabilityDescription : " + getAbilityDescription() + "\n";
	desc += "}\n";
	return desc;
}

const map<int, AbilityData*>* AbilityData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, AbilityData*>();
		static string resPath = "res/base/data/ability.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				AbilityData* abilityData = new AbilityData();
				abilityData->p_abilityId = buffer->getInt();
				p_sharedDictionary->insert(pair<int, AbilityData*>(abilityData->p_abilityId, abilityData));
			}
		}
	}
	return p_sharedDictionary;
}

AbilityData* AbilityData::getAbilityDataById(int abilityId)
{
	if (AbilityData::getSharedDictionary()->count(abilityId)) {
		return AbilityData::getSharedDictionary()->at(abilityId);
	}
	return nullptr;
}

AbilityData* AbilityData::getAbilityDataById(const string& abilityId)
{
	if (abilityId.length() == 0) return nullptr;
	return AbilityData::getAbilityDataById(atoi(abilityId.c_str()));
}

string AbilityData::getFieldValue(const string & fieldName)
{
	if (fieldName == "abilityId") {
		return to_string(this->getAbilityId());
	} else if (fieldName == "abilityName") {
		return to_string(this->getAbilityName());
	} else if (fieldName == "abilityDescription") {
		return to_string(this->getAbilityDescription());
	}
	CCLOGWARN("Couldn't recognize %s in AbilityData", fieldName.c_str());
	return "";
}

