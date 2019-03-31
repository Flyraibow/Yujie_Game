/*
This file (ClassScheduleData.cpp) is generated
*/
#include "ClassScheduleData.hpp"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, map<string,string>>* ClassScheduleData::p_sharedDictionary = nullptr;

const map<string, map<string,string>>* ClassScheduleData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, map<string,string>>();
		static string resPath = "res/base/data/classSchedule.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			vector<string> rowValues;
			auto rowCount = buffer->getLong();
			for (int i = 0; i < rowCount; ++i) {
				rowValues.push_back(buffer->getString());
			}
			vector<string> colValues;
			auto colCount = buffer->getLong();
			for (int i = 0; i < colCount; ++i) {
				colValues.push_back(buffer->getString());
			}
			for (int i = 0; i < rowCount; ++i) {
				map<string, string> rowMap;
				for (int j = 0; j < colCount; ++j) {
					string value = buffer->getString();
					rowMap.insert(make_pair(colValues[j], value));
				}
				p_sharedDictionary->insert(make_pair(rowValues[i], rowMap));
			}
		}
	}
	return p_sharedDictionary;
}

string ClassScheduleData::getClassSchedule(string date, string schooId)
{
	auto dict = getSharedDictionary();
	if (dict->count(date)) {
		if (dict->at(date).count(schooId)) {
			return dict->at(date).at(schooId);
		} else {
			CCLOGWARN("Couldn't find schooId: %s in ClassSchedule", to_string(schooId).c_str());
		}
	} else {
		CCLOGWARN("Couldn't find date: %s in ClassSchedule", to_string(date).c_str());
	}
	return 0;
}

string ClassScheduleData::getFieldValue(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ClassScheduleData", fieldName.c_str());
	return "";
}

BaseData* ClassScheduleData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ClassScheduleData", fieldName.c_str());
	return nullptr;
}

