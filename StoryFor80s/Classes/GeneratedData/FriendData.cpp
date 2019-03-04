/*
This file (FriendData.cpp) is generated
*/
#include "FriendData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, FriendData*>* FriendData::p_sharedDictionary = nullptr;

string FriendData::getId() const
{
	return to_string(p_friendId);
}

string FriendData::getFriendId() const
{
	return p_friendId;
}

string FriendData::getLastName() const
{
	string localId = "friend_lastName_" + to_string(p_friendId);
	return LocalizationHelper::getLocalization(localId);
}

string FriendData::getFirstName() const
{
	string localId = "friend_firstName_" + to_string(p_friendId);
	return LocalizationHelper::getLocalization(localId);
}

int FriendData::getBirthMonth() const
{
	return p_birthMonth;
}

int FriendData::getBirthDay() const
{
	return p_birthDay;
}

int FriendData::getGender() const
{
	return p_gender;
}

int FriendData::getRelation() const
{
	return p_relation;
}

void FriendData::setRelation(int relation)
{
	p_relation = relation;
}

string FriendData::description() const
{
	string desc = "friendData = {\n";
	desc += "\tfriendId : " + to_string(p_friendId) + "\n";
	desc += "\tlastName : " + getLastName() + "\n";
	desc += "\tfirstName : " + getFirstName() + "\n";
	desc += "\tbirthMonth : " + to_string(p_birthMonth) + "\n";
	desc += "\tbirthDay : " + to_string(p_birthDay) + "\n";
	desc += "\tgender : " + to_string(p_gender) + "\n";
	desc += "\trelation : " + to_string(p_relation) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, FriendData*>* FriendData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, FriendData*>();
		static string resPath = "res/base/data/friend.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				FriendData* friendData = new FriendData();
				friendData->p_friendId = buffer->getString();
				friendData->p_birthMonth = buffer->getInt();
				friendData->p_birthDay = buffer->getInt();
				friendData->p_gender = buffer->getInt();
				friendData->p_relation = buffer->getInt();
				p_sharedDictionary->insert(pair<string, FriendData*>(friendData->p_friendId, friendData));
			}
		}
	}
	return p_sharedDictionary;
}

FriendData* FriendData::getFriendDataById(const string& friendId)
{
	if (FriendData::getSharedDictionary()->count(friendId)) {
		return FriendData::getSharedDictionary()->at(friendId);
	}
	return nullptr;
}

bool FriendData::saveData(const string & path)
{
	auto filePath = path + "/FriendData.dat";
	auto dict = FriendData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(1);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putString(dataId);
		buffer->putString("p_relation");
		buffer->putString(to_string(data->p_relation));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool FriendData::loadData(const string & path)
{
	auto filePath = path + "/FriendData.dat";
	auto dict = FriendData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getString();
			FriendData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_relation") {
						data->p_relation = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool FriendData::clearData()
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

void FriendData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "relation") {
		this->setRelation(atoi(value.c_str()));
	}
}

string FriendData::getFieldValue(const string & fieldName)
{
	if (fieldName == "friendId") {
		return to_string(this->getFriendId());
	} else if (fieldName == "lastName") {
		return to_string(this->getLastName());
	} else if (fieldName == "firstName") {
		return to_string(this->getFirstName());
	} else if (fieldName == "birthMonth") {
		return to_string(this->getBirthMonth());
	} else if (fieldName == "birthDay") {
		return to_string(this->getBirthDay());
	} else if (fieldName == "gender") {
		return to_string(this->getGender());
	} else if (fieldName == "relation") {
		return to_string(this->getRelation());
	}
	CCLOGWARN("Couldn't recognize %s in FriendData", fieldName.c_str());
	return "";
}

BaseData* FriendData::getDataByField(const string & fieldName)
{
	CCLOGWARN("Couldn't recognize %s in FriendData", fieldName.c_str());
	return nullptr;
}

