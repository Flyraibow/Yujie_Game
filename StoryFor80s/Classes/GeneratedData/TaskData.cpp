/*
This file (TaskData.cpp) is generated
*/
#include "TaskData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, TaskData*>* TaskData::p_sharedDictionary = nullptr;

string TaskData::getId() const
{
	return to_string(p_itemId);
}

string TaskData::getItemId() const
{
	return p_itemId;
}

string TaskData::getName() const
{
	string localId = "task_name_" + to_string(p_itemId);
	return LocalizationHelper::getLocalization(localId);
}

string TaskData::getDescription() const
{
	string localId = "task_description_" + to_string(p_itemId);
	return LocalizationHelper::getLocalization(localId);
}

bool TaskData::getIsOnGoing() const
{
	return p_isOnGoing;
}

void TaskData::setIsOnGoing(bool isOnGoing)
{
	p_isOnGoing = isOnGoing;
}

bool TaskData::getFailed() const
{
	return p_failed;
}

void TaskData::setFailed(bool failed)
{
	p_failed = failed;
}

int TaskData::getStartedYear() const
{
	return p_startedYear;
}

void TaskData::setStartedYear(int startedYear)
{
	p_startedYear = startedYear;
}

int TaskData::getStartedMonth() const
{
	return p_startedMonth;
}

void TaskData::setStartedMonth(int startedMonth)
{
	p_startedMonth = startedMonth;
}

bool TaskData::getIsTimeLimited() const
{
	return p_isTimeLimited;
}

int TaskData::getLimitedMonth() const
{
	return p_limitedMonth;
}

int TaskData::getLeftMonth() const
{
	return p_leftMonth;
}

void TaskData::setLeftMonth(int leftMonth)
{
	p_leftMonth = leftMonth;
}

string TaskData::getFailCondition() const
{
	return p_failCondition;
}

SelectableScheduleData* TaskData::getForbiddenScheduleData() const
{
	return SelectableScheduleData::getSelectableScheduleDataById(p_forbiddenScheduleId);
}

string TaskData::getForbiddenScheduleId() const
{
	return p_forbiddenScheduleId;
}

string TaskData::getSuccessCondition() const
{
	return p_successCondition;
}

string TaskData::getFailedEvent() const
{
	return p_failedEvent;
}

string TaskData::getSuccessEvent() const
{
	return p_successEvent;
}

string TaskData::description() const
{
	string desc = "taskData = {\n";
	desc += "\titemId : " + to_string(p_itemId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	desc += "\tisOnGoing : " + to_string(p_isOnGoing) + "\n";
	desc += "\tfailed : " + to_string(p_failed) + "\n";
	desc += "\tstartedYear : " + to_string(p_startedYear) + "\n";
	desc += "\tstartedMonth : " + to_string(p_startedMonth) + "\n";
	desc += "\tisTimeLimited : " + to_string(p_isTimeLimited) + "\n";
	desc += "\tlimitedMonth : " + to_string(p_limitedMonth) + "\n";
	desc += "\tleftMonth : " + to_string(p_leftMonth) + "\n";
	desc += "\tfailCondition : " + to_string(p_failCondition) + "\n";
	desc += "\tforbiddenSchedule : " + to_string(p_forbiddenScheduleId) + "\n";
	desc += "\tsuccessCondition : " + to_string(p_successCondition) + "\n";
	desc += "\tfailedEvent : " + to_string(p_failedEvent) + "\n";
	desc += "\tsuccessEvent : " + to_string(p_successEvent) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, TaskData*>* TaskData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, TaskData*>();
		static string resPath = "res/base/data/task.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				TaskData* taskData = new TaskData();
				taskData->p_itemId = buffer->getString();
				taskData->p_isOnGoing = buffer->getChar();
				taskData->p_failed = buffer->getChar();
				taskData->p_startedYear = buffer->getInt();
				taskData->p_startedMonth = buffer->getInt();
				taskData->p_isTimeLimited = buffer->getChar();
				taskData->p_limitedMonth = buffer->getInt();
				taskData->p_leftMonth = buffer->getInt();
				taskData->p_failCondition = buffer->getString();
				taskData->p_forbiddenScheduleId = buffer->getString();
				taskData->p_successCondition = buffer->getString();
				taskData->p_failedEvent = buffer->getString();
				taskData->p_successEvent = buffer->getString();
				p_sharedDictionary->insert(pair<string, TaskData*>(taskData->p_itemId, taskData));
			}
		}
	}
	return p_sharedDictionary;
}

TaskData* TaskData::getTaskDataById(const string& itemId)
{
	if (TaskData::getSharedDictionary()->count(itemId)) {
		return TaskData::getSharedDictionary()->at(itemId);
	}
	return nullptr;
}

bool TaskData::saveData(const string & path)
{
	auto filePath = path + "/TaskData.dat";
	auto dict = TaskData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(5);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_isOnGoing");
		buffer->putString(to_string(data->p_isOnGoing));
		buffer->putString("p_failed");
		buffer->putString(to_string(data->p_failed));
		buffer->putString("p_startedYear");
		buffer->putString(to_string(data->p_startedYear));
		buffer->putString("p_startedMonth");
		buffer->putString(to_string(data->p_startedMonth));
		buffer->putString("p_leftMonth");
		buffer->putString(to_string(data->p_leftMonth));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool TaskData::loadData(const string & path)
{
	auto filePath = path + "/TaskData.dat";
	auto dict = TaskData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			TaskData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_isOnGoing") {
						data->p_isOnGoing = (atoi(value.c_str()) != 0);
					} else if (key == "p_failed") {
						data->p_failed = (atoi(value.c_str()) != 0);
					} else if (key == "p_startedYear") {
						data->p_startedYear = atoi(value.c_str());
					} else if (key == "p_startedMonth") {
						data->p_startedMonth = atoi(value.c_str());
					} else if (key == "p_leftMonth") {
						data->p_leftMonth = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool TaskData::clearData()
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

void TaskData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "isOnGoing") {
		this->setIsOnGoing((atoi(value.c_str()) != 0));
	} else if (fieldName == "failed") {
		this->setFailed((atoi(value.c_str()) != 0));
	} else if (fieldName == "startedYear") {
		this->setStartedYear(atoi(value.c_str()));
	} else if (fieldName == "startedMonth") {
		this->setStartedMonth(atoi(value.c_str()));
	} else if (fieldName == "leftMonth") {
		this->setLeftMonth(atoi(value.c_str()));
	}
}

string TaskData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "itemId") {
		return to_string(this->getItemId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "isOnGoing") {
		return to_string(this->getIsOnGoing());
	} else if (fieldName == "failed") {
		return to_string(this->getFailed());
	} else if (fieldName == "startedYear") {
		return to_string(this->getStartedYear());
	} else if (fieldName == "startedMonth") {
		return to_string(this->getStartedMonth());
	} else if (fieldName == "isTimeLimited") {
		return to_string(this->getIsTimeLimited());
	} else if (fieldName == "limitedMonth") {
		return to_string(this->getLimitedMonth());
	} else if (fieldName == "leftMonth") {
		return to_string(this->getLeftMonth());
	} else if (fieldName == "failCondition") {
		return to_string(this->getFailCondition());
	} else if (fieldName == "forbiddenSchedule") {
		return to_string(this->getForbiddenScheduleId());
	} else if (fieldName == "successCondition") {
		return to_string(this->getSuccessCondition());
	} else if (fieldName == "failedEvent") {
		return to_string(this->getFailedEvent());
	} else if (fieldName == "successEvent") {
		return to_string(this->getSuccessEvent());
	}
	CCLOGWARN("Couldn't recognize %s in TaskData", fieldName.c_str());
	return "";
}

BaseData* TaskData::getDataByField(const string & fieldName) const
{
	if (fieldName == "forbiddenSchedule") {
		return this->getForbiddenScheduleData();
	}
	CCLOGWARN("Couldn't recognize %s in TaskData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> TaskData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in TaskData", fieldName.c_str());
	return vector<BaseData *>();
}

