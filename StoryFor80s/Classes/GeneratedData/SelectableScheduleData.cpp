/*
This file (SelectableScheduleData.cpp) is generated
*/
#include "SelectableScheduleData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, SelectableScheduleData*>* SelectableScheduleData::p_sharedDictionary = nullptr;

string SelectableScheduleData::getId() const
{
	return to_string(p_scheduleId);
}

string SelectableScheduleData::getScheduleId() const
{
	return p_scheduleId;
}

string SelectableScheduleData::getName() const
{
	string localId = "selectableSchedule_name_" + to_string(p_scheduleId);
	return LocalizationHelper::getLocalization(localId);
}

ScheduleTypeData* SelectableScheduleData::getTypeData() const
{
	return ScheduleTypeData::getScheduleTypeDataById(p_typeId);
}

string SelectableScheduleData::getTypeId() const
{
	return p_typeId;
}

ScheduleSubTypeData* SelectableScheduleData::getSubTypeData() const
{
	return ScheduleSubTypeData::getScheduleSubTypeDataById(p_subTypeId);
}

string SelectableScheduleData::getSubTypeId() const
{
	return p_subTypeId;
}

string SelectableScheduleData::getCondition() const
{
	return p_condition;
}

ProficiencyData* SelectableScheduleData::getProficiencyData() const
{
	return ProficiencyData::getProficiencyDataById(p_proficiencyId);
}

string SelectableScheduleData::getProficiencyId() const
{
	return p_proficiencyId;
}

int SelectableScheduleData::getAddProficiency() const
{
	return p_addProficiency;
}

string SelectableScheduleData::getDescription() const
{
	string localId = "selectableSchedule_description_" + to_string(p_scheduleId);
	return LocalizationHelper::getLocalization(localId);
}

vector<BaseData *> SelectableScheduleData::getAttributeChangeList() const
{
	vector<BaseData *> v;
	for (auto iter : p_attributeChangeMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in SelectableScheduleData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> SelectableScheduleData::getAttributeChangeMap() const
{
	return p_attributeChangeMap;
}

string SelectableScheduleData::description() const
{
	string desc = "selectableScheduleData = {\n";
	desc += "\tscheduleId : " + to_string(p_scheduleId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\ttype : " + to_string(p_typeId) + "\n";
	desc += "\tsubType : " + to_string(p_subTypeId) + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tproficiency : " + to_string(p_proficiencyId) + "\n";
	desc += "\taddProficiency : " + to_string(p_addProficiency) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	
	desc += "\tattributeChange : " + to_string(p_attributeChangeMap)+ "\n";
	desc += "}\n";
	return desc;
}

const map<string, SelectableScheduleData*>* SelectableScheduleData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SelectableScheduleData*>();
		static string resPath = "res/base/data/selectableSchedule.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SelectableScheduleData* selectableScheduleData = new SelectableScheduleData();
				selectableScheduleData->p_scheduleId = buffer->getString();
				selectableScheduleData->p_typeId = buffer->getString();
				selectableScheduleData->p_subTypeId = buffer->getString();
				selectableScheduleData->p_condition = buffer->getString();
				selectableScheduleData->p_proficiencyId = buffer->getString();
				selectableScheduleData->p_addProficiency = buffer->getInt();
				auto attributeChangeCount = buffer->getLong();
				for (int j = 0; j < attributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					selectableScheduleData->p_attributeChangeMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, SelectableScheduleData*>(selectableScheduleData->p_scheduleId, selectableScheduleData));
			}
		}
	}
	return p_sharedDictionary;
}

SelectableScheduleData* SelectableScheduleData::getSelectableScheduleDataById(const string& scheduleId)
{
	if (SelectableScheduleData::getSharedDictionary()->count(scheduleId)) {
		return SelectableScheduleData::getSharedDictionary()->at(scheduleId);
	}
	return nullptr;
}

string SelectableScheduleData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "scheduleId") {
		return to_string(this->getScheduleId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "type") {
		return to_string(this->getTypeId());
	} else if (fieldName == "subType") {
		return to_string(this->getSubTypeId());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "proficiency") {
		return to_string(this->getProficiencyId());
	} else if (fieldName == "addProficiency") {
		return to_string(this->getAddProficiency());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "attributeChange") {
		return to_string(this->getAttributeChangeMap());
	}
	CCLOGWARN("Couldn't recognize %s in SelectableScheduleData", fieldName.c_str());
	return "";
}

BaseData* SelectableScheduleData::getDataByField(const string & fieldName) const
{
	if (fieldName == "type") {
		return this->getTypeData();
	} else if (fieldName == "subType") {
		return this->getSubTypeData();
	} else if (fieldName == "proficiency") {
		return this->getProficiencyData();
	}
	CCLOGWARN("Couldn't recognize %s in SelectableScheduleData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> SelectableScheduleData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "attributeChange") {
		return this->getAttributeChangeList();
	}
	CCLOGWARN("Couldn't recognize %s in SelectableScheduleData", fieldName.c_str());
	return vector<BaseData *>();
}

string SelectableScheduleData::getMapFieldValueWithKey(const string & fieldName, const string & key) const
{
	if (fieldName == "attributeChange") {
		auto fieldMap = this->getAttributeChangeMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in SelectableScheduleData", fieldName.c_str(), key.c_str());
	return "";
}

