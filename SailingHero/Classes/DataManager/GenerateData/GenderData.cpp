/*
This file (GenderData.cpp) is generated
*/
#include "GenderData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, GenderData*>* GenderData::p_sharedDictionary = nullptr;

string GenderData::getId() const
{
	return p_genderId;
}

string GenderData::getGenderId() const
{
	return p_genderId;
}

string GenderData::getGenderName() const
{
	string localId = "gender_genderName_" + p_genderId;
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

map<string, GenderData*>* GenderData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, GenderData*>();
		static string resPath = "res/base/data/gender.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GenderData* genderData = new GenderData();
				genderData->p_genderId = buffer->getString();
				p_sharedDictionary->insert(pair<string, GenderData*>(genderData->p_genderId, genderData));
			}
		}
	}
	return p_sharedDictionary;
}

GenderData* GenderData::getGenderDataById(const string& genderId)
{
	if (GenderData::getSharedDictionary()->count(genderId)) {
		return GenderData::getSharedDictionary()->at(genderId);
	}
	CCLOGERROR("invalid genderId %s", genderId.c_str());
	return nullptr;
}

