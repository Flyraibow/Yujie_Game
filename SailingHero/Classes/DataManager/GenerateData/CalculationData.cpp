/*
This file (CalculationData.cpp) is generated
*/
#include "CalculationData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, CalculationData*>* CalculationData::p_sharedDictionary = nullptr;

string CalculationData::getId() const
{
	return to_string(p_calculationId);
}

string CalculationData::getCalculationId() const
{
	return p_calculationId;
}

ConditionData* CalculationData::getConditionData() const
{
	return ConditionData::getConditionDataById(p_conditionId);
}

string CalculationData::getConditionId() const
{
	return p_conditionId;
}

string CalculationData::getYesType() const
{
	return p_yesType;
}

string CalculationData::getYesParameter() const
{
	return p_yesParameter;
}

string CalculationData::getNoType() const
{
	return p_noType;
}

string CalculationData::getNoParameter() const
{
	return p_noParameter;
}

string CalculationData::description() const
{
	string desc = "calculationData = {\n";
	desc += "\tcalculationId : " + to_string(p_calculationId) + "\n";
	desc += "\tcondition : " + to_string(p_conditionId) + "\n";
	desc += "\tyesType : " + to_string(p_yesType) + "\n";
	desc += "\tyesParameter : " + to_string(p_yesParameter) + "\n";
	desc += "\tnoType : " + to_string(p_noType) + "\n";
	desc += "\tnoParameter : " + to_string(p_noParameter) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, CalculationData*>* CalculationData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, CalculationData*>();
		static string resPath = "res/base/data/calculation.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				CalculationData* calculationData = new CalculationData();
				calculationData->p_calculationId = buffer->getString();
				calculationData->p_conditionId = buffer->getString();
				calculationData->p_yesType = buffer->getString();
				calculationData->p_yesParameter = buffer->getString();
				calculationData->p_noType = buffer->getString();
				calculationData->p_noParameter = buffer->getString();
				p_sharedDictionary->insert(pair<string, CalculationData*>(calculationData->p_calculationId, calculationData));
			}
		}
	}
	return p_sharedDictionary;
}

CalculationData* CalculationData::getCalculationDataById(const string& calculationId)
{
	if (CalculationData::getSharedDictionary()->count(calculationId)) {
		return CalculationData::getSharedDictionary()->at(calculationId);
	}
	return nullptr;
}

string CalculationData::getFieldValue(const string & fieldName)
{
	if (fieldName == "calculationId") {
		return to_string(this->getCalculationId());
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
	CCLOGWARN("Couldn't recognize %s in CalculationData", fieldName.c_str());
	return "";
}

