/*
This file (SelfStudyData.cpp) is generated
*/
#include "SelfStudyData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, SelfStudyData*>* SelfStudyData::p_sharedDictionary = nullptr;

string SelfStudyData::getId() const
{
	return to_string(p_selfStudyId);
}

string SelfStudyData::getSelfStudyId() const
{
	return p_selfStudyId;
}

string SelfStudyData::getName() const
{
	string localId = "selfStudy_name_" + to_string(p_selfStudyId);
	return LocalizationHelper::getLocalization(localId);
}

string SelfStudyData::getCondition() const
{
	return p_condition;
}

ProficiencyData* SelfStudyData::getProficiencyIdData() const
{
	return ProficiencyData::getProficiencyDataById(p_proficiencyIdId);
}

string SelfStudyData::getProficiencyIdId() const
{
	return p_proficiencyIdId;
}

int SelfStudyData::getAddProficiency() const
{
	return p_addProficiency;
}

string SelfStudyData::getDescription() const
{
	string localId = "selfStudy_description_" + to_string(p_selfStudyId);
	return LocalizationHelper::getLocalization(localId);
}

vector<BaseData *> SelfStudyData::getAttributeChangeList() const
{
	vector<BaseData *> v;
	for (auto iter : p_attributeChangeMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in SelfStudyData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> SelfStudyData::getAttributeChangeMap() const
{
	return p_attributeChangeMap;
}

string SelfStudyData::description() const
{
	string desc = "selfStudyData = {\n";
	desc += "\tselfStudyId : " + to_string(p_selfStudyId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tproficiencyId : " + to_string(p_proficiencyIdId) + "\n";
	desc += "\taddProficiency : " + to_string(p_addProficiency) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	
	desc += "\tattributeChange : " + to_string(p_attributeChangeMap)+ "\n";
	desc += "}\n";
	return desc;
}

const map<string, SelfStudyData*>* SelfStudyData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SelfStudyData*>();
		static string resPath = "res/base/data/selfStudy.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SelfStudyData* selfStudyData = new SelfStudyData();
				selfStudyData->p_selfStudyId = buffer->getString();
				selfStudyData->p_condition = buffer->getString();
				selfStudyData->p_proficiencyIdId = buffer->getString();
				selfStudyData->p_addProficiency = buffer->getInt();
				auto attributeChangeCount = buffer->getLong();
				for (int j = 0; j < attributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					selfStudyData->p_attributeChangeMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, SelfStudyData*>(selfStudyData->p_selfStudyId, selfStudyData));
			}
		}
	}
	return p_sharedDictionary;
}

SelfStudyData* SelfStudyData::getSelfStudyDataById(const string& selfStudyId)
{
	if (SelfStudyData::getSharedDictionary()->count(selfStudyId)) {
		return SelfStudyData::getSharedDictionary()->at(selfStudyId);
	}
	return nullptr;
}

string SelfStudyData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "selfStudyId") {
		return to_string(this->getSelfStudyId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "proficiencyId") {
		return to_string(this->getProficiencyIdId());
	} else if (fieldName == "addProficiency") {
		return to_string(this->getAddProficiency());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "attributeChange") {
		return to_string(this->getAttributeChangeMap());
	}
	CCLOGWARN("Couldn't recognize %s in SelfStudyData", fieldName.c_str());
	return "";
}

BaseData* SelfStudyData::getDataByField(const string & fieldName) const
{
	if (fieldName == "proficiencyId") {
		return this->getProficiencyIdData();
	}
	CCLOGWARN("Couldn't recognize %s in SelfStudyData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> SelfStudyData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "attributeChange") {
		return this->getAttributeChangeList();
	}
	CCLOGWARN("Couldn't recognize %s in SelfStudyData", fieldName.c_str());
	return vector<BaseData *>();
}

string SelfStudyData::getMapFieldValueWithKey(const string & fieldName, const string & key) const
{
	if (fieldName == "attributeChange") {
		auto fieldMap = this->getAttributeChangeMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in SelfStudyData", fieldName.c_str(), key.c_str());
	return "";
}

