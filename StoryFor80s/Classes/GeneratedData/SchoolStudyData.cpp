/*
This file (SchoolStudyData.cpp) is generated
*/
#include "SchoolStudyData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, SchoolStudyData*>* SchoolStudyData::p_sharedDictionary = nullptr;

string SchoolStudyData::getId() const
{
	return to_string(p_schoolStudyId);
}

string SchoolStudyData::getSchoolStudyId() const
{
	return p_schoolStudyId;
}

string SchoolStudyData::getName() const
{
	string localId = "schoolStudy_name_" + to_string(p_schoolStudyId);
	return LocalizationHelper::getLocalization(localId);
}

ProficiencyData* SchoolStudyData::getProficiencyIdData() const
{
	return ProficiencyData::getProficiencyDataById(p_proficiencyIdId);
}

string SchoolStudyData::getProficiencyIdId() const
{
	return p_proficiencyIdId;
}

int SchoolStudyData::getAddProficiency() const
{
	return p_addProficiency;
}

string SchoolStudyData::getDescription() const
{
	string localId = "schoolStudy_description_" + to_string(p_schoolStudyId);
	return LocalizationHelper::getLocalization(localId);
}

vector<BaseData *> SchoolStudyData::getAttributeChangeList() const
{
	vector<BaseData *> v;
	for (auto iter : p_attributeChangeMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in SchoolStudyData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> SchoolStudyData::getAttributeChangeMap() const
{
	return p_attributeChangeMap;
}

string SchoolStudyData::description() const
{
	string desc = "schoolStudyData = {\n";
	desc += "\tschoolStudyId : " + to_string(p_schoolStudyId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tproficiencyId : " + to_string(p_proficiencyIdId) + "\n";
	desc += "\taddProficiency : " + to_string(p_addProficiency) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	
	desc += "\tattributeChange : " + to_string(p_attributeChangeMap)+ "\n";
	desc += "}\n";
	return desc;
}

const map<string, SchoolStudyData*>* SchoolStudyData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SchoolStudyData*>();
		static string resPath = "res/base/data/schoolStudy.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SchoolStudyData* schoolStudyData = new SchoolStudyData();
				schoolStudyData->p_schoolStudyId = buffer->getString();
				schoolStudyData->p_proficiencyIdId = buffer->getString();
				schoolStudyData->p_addProficiency = buffer->getInt();
				auto attributeChangeCount = buffer->getLong();
				for (int j = 0; j < attributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					schoolStudyData->p_attributeChangeMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, SchoolStudyData*>(schoolStudyData->p_schoolStudyId, schoolStudyData));
			}
		}
	}
	return p_sharedDictionary;
}

SchoolStudyData* SchoolStudyData::getSchoolStudyDataById(const string& schoolStudyId)
{
	if (SchoolStudyData::getSharedDictionary()->count(schoolStudyId)) {
		return SchoolStudyData::getSharedDictionary()->at(schoolStudyId);
	}
	return nullptr;
}

string SchoolStudyData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "schoolStudyId") {
		return to_string(this->getSchoolStudyId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "proficiencyId") {
		return to_string(this->getProficiencyIdId());
	} else if (fieldName == "addProficiency") {
		return to_string(this->getAddProficiency());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "attributeChange") {
		return to_string(this->getAttributeChangeMap());
	}
	CCLOGWARN("Couldn't recognize %s in SchoolStudyData", fieldName.c_str());
	return "";
}

BaseData* SchoolStudyData::getDataByField(const string & fieldName) const
{
	if (fieldName == "proficiencyId") {
		return this->getProficiencyIdData();
	}
	CCLOGWARN("Couldn't recognize %s in SchoolStudyData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> SchoolStudyData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "attributeChange") {
		return this->getAttributeChangeList();
	}
	CCLOGWARN("Couldn't recognize %s in SchoolStudyData", fieldName.c_str());
	return vector<BaseData *>();
}

string SchoolStudyData::getMapFieldValueWithKey(const string & fieldName, const string & key) const
{
	if (fieldName == "attributeChange") {
		auto fieldMap = this->getAttributeChangeMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in SchoolStudyData", fieldName.c_str(), key.c_str());
	return "";
}

