/*
This file (DateData.cpp) is generated
*/
#include "DateData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, DateData*>* DateData::p_sharedDictionary = nullptr;

string DateData::getId() const
{
	return to_string(p_dateId);
}

string DateData::getDateId() const
{
	return p_dateId;
}

int DateData::getYear() const
{
	return p_year;
}

void DateData::setYear(int year)
{
	p_year = year;
}

int DateData::getMonth() const
{
	return p_month;
}

void DateData::setMonth(int month)
{
	p_month = month;
}

int DateData::getDay() const
{
	return p_day;
}

void DateData::setDay(int day)
{
	p_day = day;
}

string DateData::description() const
{
	string desc = "dateData = {\n";
	desc += "\tdateId : " + to_string(p_dateId) + "\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tday : " + to_string(p_day) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, DateData*>* DateData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, DateData*>();
		static string resPath = "res/base/data/date.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				DateData* dateData = new DateData();
				dateData->p_dateId = buffer->getString();
				dateData->p_year = buffer->getInt();
				dateData->p_month = buffer->getInt();
				dateData->p_day = buffer->getInt();
				p_sharedDictionary->insert(pair<string, DateData*>(dateData->p_dateId, dateData));
			}
		}
	}
	return p_sharedDictionary;
}

DateData* DateData::getDateDataById(const string& dateId)
{
	if (DateData::getSharedDictionary()->count(dateId)) {
		return DateData::getSharedDictionary()->at(dateId);
	}
	return nullptr;
}

bool DateData::saveData(const string & path)
{
	auto filePath = path + "/DateData.dat";
	auto dict = DateData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(3);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_year");
		buffer->putString(to_string(data->p_year));
		buffer->putString("p_month");
		buffer->putString(to_string(data->p_month));
		buffer->putString("p_day");
		buffer->putString(to_string(data->p_day));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool DateData::loadData(const string & path)
{
	auto filePath = path + "/DateData.dat";
	auto dict = DateData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			DateData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_year") {
						data->p_year = atoi(value.c_str());
					} else if (key == "p_month") {
						data->p_month = atoi(value.c_str());
					} else if (key == "p_day") {
						data->p_day = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool DateData::clearData()
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

void DateData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "year") {
		this->setYear(atoi(value.c_str()));
	} else if (fieldName == "month") {
		this->setMonth(atoi(value.c_str()));
	} else if (fieldName == "day") {
		this->setDay(atoi(value.c_str()));
	}
}

string DateData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "dateId") {
		return to_string(this->getDateId());
	} else if (fieldName == "year") {
		return to_string(this->getYear());
	} else if (fieldName == "month") {
		return to_string(this->getMonth());
	} else if (fieldName == "day") {
		return to_string(this->getDay());
	}
	CCLOGWARN("Couldn't recognize %s in DateData", fieldName.c_str());
	return "";
}

BaseData* DateData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in DateData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> DateData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in DateData", fieldName.c_str());
	return vector<BaseData *>();
}

