/*
This file (PlayData.cpp) is generated
*/
#include "PlayData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, PlayData*>* PlayData::p_sharedDictionary = nullptr;

string PlayData::getId() const
{
	return to_string(p_playId);
}

string PlayData::getPlayId() const
{
	return p_playId;
}

string PlayData::getName() const
{
	string localId = "play_name_" + to_string(p_playId);
	return LocalizationHelper::getLocalization(localId);
}

string PlayData::getCondition() const
{
	return p_condition;
}

int PlayData::getExpense() const
{
	return p_expense;
}

ProficiencyData* PlayData::getProficienceData() const
{
	return ProficiencyData::getProficiencyDataById(p_proficienceId);
}

string PlayData::getProficienceId() const
{
	return p_proficienceId;
}

int PlayData::getAddProficiency() const
{
	return p_addProficiency;
}

string PlayData::getDescription() const
{
	string localId = "play_description_" + to_string(p_playId);
	return LocalizationHelper::getLocalization(localId);
}

vector<BaseData *> PlayData::getAttributeChangeList() const
{
	vector<BaseData *> v;
	for (auto iter : p_attributeChangeMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in PlayData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> PlayData::getAttributeChangeMap() const
{
	return p_attributeChangeMap;
}

string PlayData::description() const
{
	string desc = "playData = {\n";
	desc += "\tplayId : " + to_string(p_playId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\texpense : " + to_string(p_expense) + "\n";
	desc += "\tproficience : " + to_string(p_proficienceId) + "\n";
	desc += "\taddProficiency : " + to_string(p_addProficiency) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	
	desc += "\tattributeChange : " + to_string(p_attributeChangeMap)+ "\n";
	desc += "}\n";
	return desc;
}

const map<string, PlayData*>* PlayData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, PlayData*>();
		static string resPath = "res/base/data/play.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				PlayData* playData = new PlayData();
				playData->p_playId = buffer->getString();
				playData->p_condition = buffer->getString();
				playData->p_expense = buffer->getInt();
				playData->p_proficienceId = buffer->getString();
				playData->p_addProficiency = buffer->getInt();
				auto attributeChangeCount = buffer->getLong();
				for (int j = 0; j < attributeChangeCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					playData->p_attributeChangeMap.insert(make_pair(key, val));
				}
				p_sharedDictionary->insert(pair<string, PlayData*>(playData->p_playId, playData));
			}
		}
	}
	return p_sharedDictionary;
}

PlayData* PlayData::getPlayDataById(const string& playId)
{
	if (PlayData::getSharedDictionary()->count(playId)) {
		return PlayData::getSharedDictionary()->at(playId);
	}
	return nullptr;
}

string PlayData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "playId") {
		return to_string(this->getPlayId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "expense") {
		return to_string(this->getExpense());
	} else if (fieldName == "proficience") {
		return to_string(this->getProficienceId());
	} else if (fieldName == "addProficiency") {
		return to_string(this->getAddProficiency());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	} else if (fieldName == "attributeChange") {
		return to_string(this->getAttributeChangeMap());
	}
	CCLOGWARN("Couldn't recognize %s in PlayData", fieldName.c_str());
	return "";
}

BaseData* PlayData::getDataByField(const string & fieldName) const
{
	if (fieldName == "proficience") {
		return this->getProficienceData();
	}
	CCLOGWARN("Couldn't recognize %s in PlayData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> PlayData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "attributeChange") {
		return this->getAttributeChangeList();
	}
	CCLOGWARN("Couldn't recognize %s in PlayData", fieldName.c_str());
	return vector<BaseData *>();
}

string PlayData::getMapFieldValueWithKey(const string & fieldName, const string & key) const
{
	if (fieldName == "attributeChange") {
		auto fieldMap = this->getAttributeChangeMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in PlayData", fieldName.c_str(), key.c_str());
	return "";
}

