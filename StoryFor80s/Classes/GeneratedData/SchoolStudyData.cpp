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

ScheduleTypeData* SchoolStudyData::getTypeData() const
{
	return ScheduleTypeData::getScheduleTypeDataById(p_typeId);
}

string SchoolStudyData::getTypeId() const
{
	return p_typeId;
}

ProficiencyData* SchoolStudyData::getProficiencyData() const
{
	return ProficiencyData::getProficiencyDataById(p_proficiencyId);
}

string SchoolStudyData::getProficiencyId() const
{
	return p_proficiencyId;
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

vector<BaseData *> SchoolStudyData::getProficiencyDependOnList() const
{
	vector<BaseData *> v;
	for (auto iter : p_proficiencyDependOnMap) {
		ProficiencyData *data = ProficiencyData::getProficiencyDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as ProficiencyData in SchoolStudyData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> SchoolStudyData::getProficiencyDependOnMap() const
{
	return p_proficiencyDependOnMap;
}

int SchoolStudyData::getStopGrowAt() const
{
	return p_stopGrowAt;
}

string SchoolStudyData::description() const
{
	string desc = "schoolStudyData = {\n";
	desc += "\tschoolStudyId : " + to_string(p_schoolStudyId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\ttype : " + to_string(p_typeId) + "\n";
	desc += "\tproficiency : " + to_string(p_proficiencyId) + "\n";
	desc += "\taddProficiency : " + to_string(p_addProficiency) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	
	desc += "\tattributeChange : " + to_string(p_attributeChangeMap)+ "\n";
	
	desc += "\tproficiencyDependOn : " + to_string(p_proficiencyDependOnMap)+ "\n";
	desc += "\tstopGrowAt : " + to_string(p_stopGrowAt) + "\n";
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
				schoolStudyData->p_typeId = buffer->getString();
				schoolStudyData->p_proficiencyId = buffer->getString();
				schoolStudyData->p_addProficiency = buffer->getInt();
				auto attributeChangeCount = buffer->getLong();
				for (int j = 0; j < attributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					schoolStudyData->p_attributeChangeMap.insert(make_pair(key, val));
				}
				auto proficiencyDependOnCount = buffer->getLong();
				for (int j = 0; j < proficiencyDependOnCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					schoolStudyData->p_proficiencyDependOnMap.insert(make_pair(key, val));
				}
				schoolStudyData->p_stopGrowAt = buffer->getInt();
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
	} else if (fieldName == "type") {
		return to_string(this->getTypeId());
	} else if (fieldName == "proficiency") {
		return to_string(this->getProficiencyId());
	} else if (fieldName == "addProficiency") {
		return to_string(this->getAddProficiency());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "attributeChange") {
		return to_string(this->getAttributeChangeMap());
	} else if (fieldName == "proficiencyDependOn") {
		return to_string(this->getProficiencyDependOnMap());
	} else if (fieldName == "stopGrowAt") {
		return to_string(this->getStopGrowAt());
	}
	CCLOGWARN("Couldn't recognize %s in SchoolStudyData", fieldName.c_str());
	return "";
}

BaseData* SchoolStudyData::getDataByField(const string & fieldName) const
{
	if (fieldName == "type") {
		return this->getTypeData();
	} else if (fieldName == "proficiency") {
		return this->getProficiencyData();
	}
	CCLOGWARN("Couldn't recognize %s in SchoolStudyData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> SchoolStudyData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "attributeChange") {
		return this->getAttributeChangeList();
	} else if (fieldName == "proficiencyDependOn") {
		return this->getProficiencyDependOnList();
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
	} else if (fieldName == "proficiencyDependOn") {
		auto fieldMap = this->getProficiencyDependOnMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in SchoolStudyData", fieldName.c_str(), key.c_str());
	return "";
}

