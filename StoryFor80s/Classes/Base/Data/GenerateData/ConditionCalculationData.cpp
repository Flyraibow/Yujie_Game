/*
This file (ConditionCalculationData.cpp) is generated
*/
#include "ConditionCalculationData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, ConditionCalculationData*>* ConditionCalculationData::p_sharedDictionary = nullptr;

string ConditionCalculationData::getId() const
{
	return to_string(p_conditionCalculationId);
}

string ConditionCalculationData::getConditionCalculationId() const
{
	return p_conditionCalculationId;
}

ConditionData* ConditionCalculationData::getConditionData() const
{
	return ConditionData::getConditionDataById(p_conditionId);
}

string ConditionCalculationData::getConditionId() const
{
	return p_conditionId;
}

string ConditionCalculationData::getYesType() const
{
	return p_yesType;
}

string ConditionCalculationData::getYesParameter() const
{
	return p_yesParameter;
}

string ConditionCalculationData::getNoType() const
{
	return p_noType;
}

string ConditionCalculationData::getNoParameter() const
{
	return p_noParameter;
}

string ConditionCalculationData::description() const
{
	string desc = "conditionCalculationData = {\n";
	desc += "\tconditionCalculationId : " + to_string(p_conditionCalculationId) + "\n";
	desc += "\tcondition : " + to_string(p_conditionId) + "\n";
	desc += "\tyesType : " + to_string(p_yesType) + "\n";
	desc += "\tyesParameter : " + to_string(p_yesParameter) + "\n";
	desc += "\tnoType : " + to_string(p_noType) + "\n";
	desc += "\tnoParameter : " + to_string(p_noParameter) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ConditionCalculationData*>* ConditionCalculationData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ConditionCalculationData*>();
		static string resPath = "res/base/data/conditionCalculation.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ConditionCalculationData* conditionCalculationData = new ConditionCalculationData();
				conditionCalculationData->p_conditionCalculationId = buffer->getString();
				conditionCalculationData->p_conditionId = buffer->getString();
				conditionCalculationData->p_yesType = buffer->getString();
				conditionCalculationData->p_yesParameter = buffer->getString();
				conditionCalculationData->p_noType = buffer->getString();
				conditionCalculationData->p_noParameter = buffer->getString();
				p_sharedDictionary->insert(pair<string, ConditionCalculationData*>(conditionCalculationData->p_conditionCalculationId, conditionCalculationData));
			}
		}
	}
	return p_sharedDictionary;
}

ConditionCalculationData* ConditionCalculationData::getConditionCalculationDataById(const string& conditionCalculationId)
{
	if (ConditionCalculationData::getSharedDictionary()->count(conditionCalculationId)) {
		return ConditionCalculationData::getSharedDictionary()->at(conditionCalculationId);
	}
	return nullptr;
}

string ConditionCalculationData::getFieldValue(const string & fieldName)
{
	if (fieldName == "conditionCalculationId") {
		return to_string(this->getConditionCalculationId());
	} else if (fieldName == "condition") {
		return to_string(this->getConditionId());
	} else if (fieldName == "yesType") {
		return to_string(this->getYesType());
	} else if (fieldName == "yesParameter") {
		return to_string(this->getYesParameter());
	} else if (fieldName == "noType") {
		return to_string(this->getNoType());
	} else if (fieldName == "noParameter") {
		return to_string(this->getNoParameter());
	}
	CCLOGWARN("Couldn't recognize %s in ConditionCalculationData", fieldName.c_str());
	return "";
}

