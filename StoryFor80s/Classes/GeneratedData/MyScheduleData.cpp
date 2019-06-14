/*
This file (MyScheduleData.cpp) is generated
*/
#include "MyScheduleData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, MyScheduleData*>* MyScheduleData::p_sharedDictionary = nullptr;

string MyScheduleData::getId() const
{
	return to_string(p_myScheduleId);
}

string MyScheduleData::getMyScheduleId() const
{
	return p_myScheduleId;
}

string MyScheduleData::getCondition() const
{
	return p_condition;
}

bool MyScheduleData::getLocked() const
{
	return p_locked;
}

void MyScheduleData::setLocked(bool locked)
{
	p_locked = locked;
}

ScheduleTypeData* MyScheduleData::getTypeData() const
{
	return ScheduleTypeData::getScheduleTypeDataById(p_typeId);
}

string MyScheduleData::getTypeId() const
{
	return p_typeId;
}

void MyScheduleData::setTypeId(string type)
{
	p_typeId = type;
}

SelectableScheduleData* MyScheduleData::getScheduleData() const
{
	return SelectableScheduleData::getSelectableScheduleDataById(p_scheduleId);
}

string MyScheduleData::getScheduleId() const
{
	return p_scheduleId;
}

void MyScheduleData::setScheduleId(string schedule)
{
	p_scheduleId = schedule;
}

string MyScheduleData::description() const
{
	string desc = "myScheduleData = {\n";
	desc += "\tmyScheduleId : " + to_string(p_myScheduleId) + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tlocked : " + to_string(p_locked) + "\n";
	desc += "\ttype : " + to_string(p_typeId) + "\n";
	desc += "\tschedule : " + to_string(p_scheduleId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, MyScheduleData*>* MyScheduleData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, MyScheduleData*>();
		static string resPath = "res/base/data/mySchedule.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				MyScheduleData* myScheduleData = new MyScheduleData();
				myScheduleData->p_myScheduleId = buffer->getString();
				myScheduleData->p_condition = buffer->getString();
				myScheduleData->p_locked = buffer->getChar();
				myScheduleData->p_typeId = buffer->getString();
				myScheduleData->p_scheduleId = buffer->getString();
				p_sharedDictionary->insert(pair<string, MyScheduleData*>(myScheduleData->p_myScheduleId, myScheduleData));
			}
		}
	}
	return p_sharedDictionary;
}

MyScheduleData* MyScheduleData::getMyScheduleDataById(const string& myScheduleId)
{
	if (MyScheduleData::getSharedDictionary()->count(myScheduleId)) {
		return MyScheduleData::getSharedDictionary()->at(myScheduleId);
	}
	return nullptr;
}

bool MyScheduleData::saveData(const string & path)
{
	auto filePath = path + "/MyScheduleData.dat";
	auto dict = MyScheduleData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(3);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_locked");
		buffer->putString(to_string(data->p_locked));
		buffer->putString("p_typeId");
		buffer->putString(to_string(data->p_typeId));
		buffer->putString("p_scheduleId");
		buffer->putString(to_string(data->p_scheduleId));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool MyScheduleData::loadData(const string & path)
{
	auto filePath = path + "/MyScheduleData.dat";
	auto dict = MyScheduleData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			MyScheduleData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_locked") {
						data->p_locked = (atoi(value.c_str()) != 0);
					} else if (key == "p_typeId") {
						data->p_typeId = value;
					} else if (key == "p_scheduleId") {
						data->p_scheduleId = value;
					}
				}
			}
		}
	}
	return true;
}

bool MyScheduleData::clearData()
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

void MyScheduleData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "locked") {
		this->setLocked((atoi(value.c_str()) != 0));
	} else if (fieldName == "type") {
		this->setTypeId(value);
	} else if (fieldName == "schedule") {
		this->setScheduleId(value);
	}
}

string MyScheduleData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "myScheduleId") {
		return to_string(this->getMyScheduleId());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "locked") {
		return to_string(this->getLocked());
	} else if (fieldName == "type") {
		return to_string(this->getTypeId());
	} else if (fieldName == "schedule") {
		return to_string(this->getScheduleId());
	}
	CCLOGWARN("Couldn't recognize %s in MyScheduleData", fieldName.c_str());
	return "";
}

BaseData* MyScheduleData::getDataByField(const string & fieldName) const
{
	if (fieldName == "type") {
		return this->getTypeData();
	} else if (fieldName == "schedule") {
		return this->getScheduleData();
	}
	CCLOGWARN("Couldn't recognize %s in MyScheduleData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> MyScheduleData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in MyScheduleData", fieldName.c_str());
	return vector<BaseData *>();
}

