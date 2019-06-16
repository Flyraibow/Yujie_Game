/*
This file (ProficiencyCategoryData.cpp) is generated
*/
#include "ProficiencyCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ProficiencyCategoryData*>* ProficiencyCategoryData::p_sharedDictionary = nullptr;

string ProficiencyCategoryData::getId() const
{
	return to_string(p_proficiencyCategoryId);
}

string ProficiencyCategoryData::getProficiencyCategoryId() const
{
	return p_proficiencyCategoryId;
}

string ProficiencyCategoryData::getName() const
{
	string localId = "proficiencyCategory_name_" + to_string(p_proficiencyCategoryId);
	return LocalizationHelper::getLocalization(localId);
}

string ProficiencyCategoryData::description() const
{
	string desc = "proficiencyCategoryData = {\n";
	desc += "\tproficiencyCategoryId : " + to_string(p_proficiencyCategoryId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ProficiencyCategoryData*>* ProficiencyCategoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ProficiencyCategoryData*>();
		static string resPath = "res/base/data/proficiencyCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ProficiencyCategoryData* proficiencyCategoryData = new ProficiencyCategoryData();
				proficiencyCategoryData->p_proficiencyCategoryId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ProficiencyCategoryData*>(proficiencyCategoryData->p_proficiencyCategoryId, proficiencyCategoryData));
			}
		}
	}
	return p_sharedDictionary;
}

ProficiencyCategoryData* ProficiencyCategoryData::getProficiencyCategoryDataById(const string& proficiencyCategoryId)
{
	if (ProficiencyCategoryData::getSharedDictionary()->count(proficiencyCategoryId)) {
		return ProficiencyCategoryData::getSharedDictionary()->at(proficiencyCategoryId);
	}
	return nullptr;
}

string ProficiencyCategoryData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "proficiencyCategoryId") {
		return to_string(this->getProficiencyCategoryId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	}
	CCLOGWARN("Couldn't recognize %s in ProficiencyCategoryData", fieldName.c_str());
	return "";
}

BaseData* ProficiencyCategoryData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ProficiencyCategoryData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ProficiencyCategoryData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ProficiencyCategoryData", fieldName.c_str());
	return vector<BaseData *>();
}

