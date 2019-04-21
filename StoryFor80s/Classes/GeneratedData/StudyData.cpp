/*
This file (StudyData.cpp) is generated
*/
#include "StudyData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, StudyData*>* StudyData::p_sharedDictionary = nullptr;

string StudyData::getId() const
{
	return to_string(p_studyId);
}

string StudyData::getStudyId() const
{
	return p_studyId;
}

string StudyData::getName() const
{
	string localId = "study_name_" + to_string(p_studyId);
	return LocalizationHelper::getLocalization(localId);
}

string StudyData::getStudyCondition() const
{
	return p_studyCondition;
}

int StudyData::getMaxValue() const
{
	return p_maxValue;
}

int StudyData::getPassValue() const
{
	return p_passValue;
}

int StudyData::getValue() const
{
	return p_value;
}

void StudyData::setValue(int value)
{
	p_value = value;
}

set<StudyData*> StudyData::getRequiresDataSet() const
{
	set<StudyData*> resultSet;
	for (auto objId : p_requiresIdSet) {
		resultSet.insert(StudyData::getStudyDataById(objId));
	}
	return resultSet;
}

set<string> StudyData::getRequiresIdSet() const
{
	return p_requiresIdSet;
}

string StudyData::getDescription() const
{
	string localId = "study_description_" + to_string(p_studyId);
	return LocalizationHelper::getLocalization(localId);
}

vector<BaseData *> StudyData::getSchoolAttributeChangeList() const
{
	vector<BaseData *> v;
	for (auto iter : p_schoolAttributeChangeMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in StudyData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> StudyData::getSchoolAttributeChangeMap() const
{
	return p_schoolAttributeChangeMap;
}

vector<BaseData *> StudyData::getSelfstudyAttributeChangeList() const
{
	vector<BaseData *> v;
	for (auto iter : p_selfstudyAttributeChangeMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in StudyData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> StudyData::getSelfstudyAttributeChangeMap() const
{
	return p_selfstudyAttributeChangeMap;
}

string StudyData::description() const
{
	string desc = "studyData = {\n";
	desc += "\tstudyId : " + to_string(p_studyId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tstudyCondition : " + to_string(p_studyCondition) + "\n";
	desc += "\tmaxValue : " + to_string(p_maxValue) + "\n";
	desc += "\tpassValue : " + to_string(p_passValue) + "\n";
	desc += "\tvalue : " + to_string(p_value) + "\n";
	desc += "\trequires : " + to_string(p_requiresIdSet) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	
	desc += "\tschoolAttributeChange : " + to_string(p_schoolAttributeChangeMap)+ "\n";
	
	desc += "\tselfstudyAttributeChange : " + to_string(p_selfstudyAttributeChangeMap)+ "\n";
	desc += "}\n";
	return desc;
}

const map<string, StudyData*>* StudyData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, StudyData*>();
		static string resPath = "res/base/data/study.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				StudyData* studyData = new StudyData();
				studyData->p_studyId = buffer->getString();
				studyData->p_studyCondition = buffer->getString();
				studyData->p_maxValue = buffer->getInt();
				studyData->p_passValue = buffer->getInt();
				studyData->p_value = buffer->getInt();
				auto requiresCount = buffer->getLong();
				for (int j = 0; j < requiresCount; ++j) {
					studyData->p_requiresIdSet.insert(buffer->getString());
				}
				auto schoolAttributeChangeCount = buffer->getLong();
				for (int j = 0; j < schoolAttributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					studyData->p_schoolAttributeChangeMap.insert(make_pair(key, val));
				}
				auto selfstudyAttributeChangeCount = buffer->getLong();
				for (int j = 0; j < selfstudyAttributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					studyData->p_selfstudyAttributeChangeMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, StudyData*>(studyData->p_studyId, studyData));
			}
		}
	}
	return p_sharedDictionary;
}

StudyData* StudyData::getStudyDataById(const string& studyId)
{
	if (StudyData::getSharedDictionary()->count(studyId)) {
		return StudyData::getSharedDictionary()->at(studyId);
	}
	return nullptr;
}

bool StudyData::saveData(const string & path)
{
	auto filePath = path + "/StudyData.dat";
	auto dict = StudyData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_value");
		buffer->putString(to_string(data->p_value));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool StudyData::loadData(const string & path)
{
	auto filePath = path + "/StudyData.dat";
	auto dict = StudyData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			StudyData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_value") {
						data->p_value = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool StudyData::clearData()
{
	if (p_sharedDictionary != nullptr) {
		for (auto iter = p_sharedDictionary->begin(); iter != p_sharedDictionary->end(); ++iter) {
			auto data = iter->second;
			delete data;
		}
		delete p_sharedDictionary;
		p_sharedDictionary = nullptr;
	}
	return true;
}

void StudyData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "value") {
		this->setValue(atoi(value.c_str()));
	}
}

string StudyData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "studyId") {
		return to_string(this->getStudyId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "studyCondition") {
		return to_string(this->getStudyCondition());
	} else if (fieldName == "maxValue") {
		return to_string(this->getMaxValue());
	} else if (fieldName == "passValue") {
		return to_string(this->getPassValue());
	} else if (fieldName == "value") {
		return to_string(this->getValue());
	} else if (fieldName == "requires") {
		return to_string(this->getRequiresIdSet());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "schoolAttributeChange") {
		return to_string(this->getSchoolAttributeChangeMap());
	} else if (fieldName == "selfstudyAttributeChange") {
		return to_string(this->getSelfstudyAttributeChangeMap());
	}
	CCLOGWARN("Couldn't recognize %s in StudyData", fieldName.c_str());
	return "";
}

BaseData* StudyData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in StudyData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> StudyData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "schoolAttributeChange") {
		return this->getSchoolAttributeChangeList();
	} else if (fieldName == "selfstudyAttributeChange") {
		return this->getSelfstudyAttributeChangeList();
	}
	CCLOGWARN("Couldn't recognize %s in StudyData", fieldName.c_str());
	return vector<BaseData *>();
}

string StudyData::getMapFieldValueWithKey(const string & fieldName, const string & key) const
{
	if (fieldName == "schoolAttributeChange") {
		auto fieldMap = this->getSchoolAttributeChangeMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	} else if (fieldName == "selfstudyAttributeChange") {
		auto fieldMap = this->getSelfstudyAttributeChangeMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in StudyData", fieldName.c_str(), key.c_str());
	return "";
}

