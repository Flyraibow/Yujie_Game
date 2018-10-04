/*
This file (GenderData.cpp) is generated
*/
#include "GenderData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<int, GenderData*>* GenderData::p_sharedDictionary = nullptr;

string GenderData::getId() const
{
	return to_string(p_genderId);
}

int GenderData::getGenderId() const
{
	return p_genderId;
}

string GenderData::getGenderName() const
{
	string localId = "gender_genderName_" + to_string(p_genderId);
	return LocalizationHelper::getLocalization(localId);
}

string GenderData::description() const
{
	string desc = "genderData = {\n";
	desc += "\tgenderId : " + to_string(p_genderId) + "\n";
	desc += "\tgenderName : " + getGenderName() + "\n";
	desc += "}\n";
	return desc;
}

const map<int, GenderData*>* GenderData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, GenderData*>();
		static string resPath = "res/base/data/gender.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GenderData* genderData = new GenderData();
				genderData->p_genderId = buffer->getInt();
				p_sharedDictionary->insert(pair<int, GenderData*>(genderData->p_genderId, genderData));
			}
		}
	}
	return p_sharedDictionary;
}

GenderData* GenderData::getGenderDataById(int genderId)
{
	if (GenderData::getSharedDictionary()->count(genderId)) {
		return GenderData::getSharedDictionary()->at(genderId);
	}
	return nullptr;
}

GenderData* GenderData::getGenderDataById(const string& genderId)
{
	if (genderId.length() == 0) return nullptr;
	return GenderData::getGenderDataById(atoi(genderId.c_str()));
}

string GenderData::getFieldValue(const string & fieldName)
{
	if (fieldName == "genderId") {
		return to_string(this->getGenderId());
	} else if (fieldName == "genderName") {
		return to_string(this->getGenderName());
	}
	CCLOGWARN("Couldn't recognize %s in GenderData", fieldName.c_str());
	return "";
}

