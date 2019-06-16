/*
This file (ExamData.cpp) is generated
*/
#include "ExamData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ExamData*>* ExamData::p_sharedDictionary = nullptr;

string ExamData::getId() const
{
	return to_string(p_examId);
}

string ExamData::getExamId() const
{
	return p_examId;
}

string ExamData::getName() const
{
	string localId = "exam_name_" + to_string(p_examId);
	return LocalizationHelper::getLocalization(localId);
}

int ExamData::getBaseValue() const
{
	return p_baseValue;
}

vector<BaseData *> ExamData::getBaseProficiencyRequirementsList() const
{
	vector<BaseData *> v;
	for (auto iter : p_baseProficiencyRequirementsMap) {
		ProficiencyData *data = ProficiencyData::getProficiencyDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as ProficiencyData in ExamData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> ExamData::getBaseProficiencyRequirementsMap() const
{
	return p_baseProficiencyRequirementsMap;
}

int ExamData::getMidValue() const
{
	return p_midValue;
}

vector<BaseData *> ExamData::getMidProficiencyRequirementsList() const
{
	vector<BaseData *> v;
	for (auto iter : p_midProficiencyRequirementsMap) {
		ProficiencyData *data = ProficiencyData::getProficiencyDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as ProficiencyData in ExamData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> ExamData::getMidProficiencyRequirementsMap() const
{
	return p_midProficiencyRequirementsMap;
}

int ExamData::getHighValue() const
{
	return p_highValue;
}

vector<BaseData *> ExamData::getHighProficiencyRequirementsList() const
{
	vector<BaseData *> v;
	for (auto iter : p_highProficiencyRequirementsMap) {
		ProficiencyData *data = ProficiencyData::getProficiencyDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as ProficiencyData in ExamData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> ExamData::getHighProficiencyRequirementsMap() const
{
	return p_highProficiencyRequirementsMap;
}

vector<BaseData *> ExamData::getHighAttributeRequirementsList() const
{
	vector<BaseData *> v;
	for (auto iter : p_highAttributeRequirementsMap) {
		AttributeData *data = AttributeData::getAttributeDataById(iter.first);
		if (data != nullptr) {
			v.push_back(data);
		} else {
			CCLOGWARN("Couldn't recognize %s as AttributeData in ExamData", iter.first.c_str());
		}
	}
	return v;
}

map<string, int> ExamData::getHighAttributeRequirementsMap() const
{
	return p_highAttributeRequirementsMap;
}

int ExamData::getLowestScore() const
{
	return p_lowestScore;
}

int ExamData::getMidScore() const
{
	return p_midScore;
}

int ExamData::getHighestScore() const
{
	return p_highestScore;
}

AchievementsData* ExamData::getRankAchievementData() const
{
	return AchievementsData::getAchievementsDataById(p_rankAchievementId);
}

string ExamData::getRankAchievementId() const
{
	return p_rankAchievementId;
}

AchievementsData* ExamData::getScoreAchievementData() const
{
	return AchievementsData::getAchievementsDataById(p_scoreAchievementId);
}

string ExamData::getScoreAchievementId() const
{
	return p_scoreAchievementId;
}

string ExamData::description() const
{
	string desc = "examData = {\n";
	desc += "\texamId : " + to_string(p_examId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tbaseValue : " + to_string(p_baseValue) + "\n";
	
	desc += "\tbaseProficiencyRequirements : " + to_string(p_baseProficiencyRequirementsMap)+ "\n";
	desc += "\tmidValue : " + to_string(p_midValue) + "\n";
	
	desc += "\tmidProficiencyRequirements : " + to_string(p_midProficiencyRequirementsMap)+ "\n";
	desc += "\thighValue : " + to_string(p_highValue) + "\n";
	
	desc += "\thighProficiencyRequirements : " + to_string(p_highProficiencyRequirementsMap)+ "\n";
	
	desc += "\thighAttributeRequirements : " + to_string(p_highAttributeRequirementsMap)+ "\n";
	desc += "\tlowestScore : " + to_string(p_lowestScore) + "\n";
	desc += "\tmidScore : " + to_string(p_midScore) + "\n";
	desc += "\thighestScore : " + to_string(p_highestScore) + "\n";
	desc += "\trankAchievement : " + to_string(p_rankAchievementId) + "\n";
	desc += "\tscoreAchievement : " + to_string(p_scoreAchievementId) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ExamData*>* ExamData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ExamData*>();
		static string resPath = "res/base/data/exam.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ExamData* examData = new ExamData();
				examData->p_examId = buffer->getString();
				examData->p_baseValue = buffer->getInt();
				auto baseProficiencyRequirementsCount = buffer->getLong();
				for (int j = 0; j < baseProficiencyRequirementsCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					examData->p_baseProficiencyRequirementsMap.insert(make_pair(key, val));
				}
				examData->p_midValue = buffer->getInt();
				auto midProficiencyRequirementsCount = buffer->getLong();
				for (int j = 0; j < midProficiencyRequirementsCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					examData->p_midProficiencyRequirementsMap.insert(make_pair(key, val));
				}
				examData->p_highValue = buffer->getInt();
				auto highProficiencyRequirementsCount = buffer->getLong();
				for (int j = 0; j < highProficiencyRequirementsCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					examData->p_highProficiencyRequirementsMap.insert(make_pair(key, val));
				}
				auto highAttributeRequirementsCount = buffer->getLong();
				for (int j = 0; j < highAttributeRequirementsCount; ++j) {
					auto key = buffer->getString();
					auto val = buffer->getInt();
					examData->p_highAttributeRequirementsMap.insert(make_pair(key, val));
				}
				examData->p_lowestScore = buffer->getInt();
				examData->p_midScore = buffer->getInt();
				examData->p_highestScore = buffer->getInt();
				examData->p_rankAchievementId = buffer->getString();
				examData->p_scoreAchievementId = buffer->getString();
				p_sharedDictionary->insert(pair<string, ExamData*>(examData->p_examId, examData));
			}
		}
	}
	return p_sharedDictionary;
}

ExamData* ExamData::getExamDataById(const string& examId)
{
	if (ExamData::getSharedDictionary()->count(examId)) {
		return ExamData::getSharedDictionary()->at(examId);
	}
	return nullptr;
}

string ExamData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "examId") {
		return to_string(this->getExamId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "baseValue") {
		return to_string(this->getBaseValue());
	} else if (fieldName == "baseProficiencyRequirements") {
		return to_string(this->getBaseProficiencyRequirementsMap());
	} else if (fieldName == "midValue") {
		return to_string(this->getMidValue());
	} else if (fieldName == "midProficiencyRequirements") {
		return to_string(this->getMidProficiencyRequirementsMap());
	} else if (fieldName == "highValue") {
		return to_string(this->getHighValue());
	} else if (fieldName == "highProficiencyRequirements") {
		return to_string(this->getHighProficiencyRequirementsMap());
	} else if (fieldName == "highAttributeRequirements") {
		return to_string(this->getHighAttributeRequirementsMap());
	} else if (fieldName == "lowestScore") {
		return to_string(this->getLowestScore());
	} else if (fieldName == "midScore") {
		return to_string(this->getMidScore());
	} else if (fieldName == "highestScore") {
		return to_string(this->getHighestScore());
	} else if (fieldName == "rankAchievement") {
		return to_string(this->getRankAchievementId());
	} else if (fieldName == "scoreAchievement") {
		return to_string(this->getScoreAchievementId());
	}
	CCLOGWARN("Couldn't recognize %s in ExamData", fieldName.c_str());
	return "";
}

BaseData* ExamData::getDataByField(const string & fieldName) const
{
	if (fieldName == "rankAchievement") {
		return this->getRankAchievementData();
	} else if (fieldName == "scoreAchievement") {
		return this->getScoreAchievementData();
	}
	CCLOGWARN("Couldn't recognize %s in ExamData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ExamData::getFieldDataList(const string & fieldName) const
{
	if (fieldName == "baseProficiencyRequirements") {
		return this->getBaseProficiencyRequirementsList();
	} else if (fieldName == "midProficiencyRequirements") {
		return this->getMidProficiencyRequirementsList();
	} else if (fieldName == "highProficiencyRequirements") {
		return this->getHighProficiencyRequirementsList();
	} else if (fieldName == "highAttributeRequirements") {
		return this->getHighAttributeRequirementsList();
	}
	CCLOGWARN("Couldn't recognize %s in ExamData", fieldName.c_str());
	return vector<BaseData *>();
}

string ExamData::getMapFieldValueWithKey(const string & fieldName, const string & key) const
{
	if (fieldName == "baseProficiencyRequirements") {
		auto fieldMap = this->getBaseProficiencyRequirementsMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	} else if (fieldName == "midProficiencyRequirements") {
		auto fieldMap = this->getMidProficiencyRequirementsMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	} else if (fieldName == "highProficiencyRequirements") {
		auto fieldMap = this->getHighProficiencyRequirementsMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	} else if (fieldName == "highAttributeRequirements") {
		auto fieldMap = this->getHighAttributeRequirementsMap();
		if (fieldMap.count(key)) {
			return to_string(fieldMap.at(key));
		}
	}
	CCLOGWARN("Couldn't recognize field: %s, key: %s in ExamData", fieldName.c_str(), key.c_str());
	return "";
}

