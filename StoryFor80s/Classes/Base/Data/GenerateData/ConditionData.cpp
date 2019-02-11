/*
This file (ConditionData.cpp) is generated
*/
#include "ConditionData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace SHUtil;

map<string, ConditionData*>* ConditionData::p_sharedDictionary = nullptr;

string ConditionData::getId() const
{
	return to_string(p_conditionId);
}

string ConditionData::getConditionId() const
{
	return p_conditionId;
}

string ConditionData::getLeftType() const
{
	return p_leftType;
}

string ConditionData::getLeftParameter() const
{
	return p_leftParameter;
}

string ConditionData::getCompareFunction() const
{
	return p_compareFunction;
}

string ConditionData::getRightType() const
{
	return p_rightType;
}

string ConditionData::getRightParameter() const
{
	return p_rightParameter;
}

string ConditionData::description() const
{
	string desc = "conditionData = {\n";
	desc += "\tconditionId : " + to_string(p_conditionId) + "\n";
	desc += "\tleftType : " + to_string(p_leftType) + "\n";
	desc += "\tleftParameter : " + to_string(p_leftParameter) + "\n";
	desc += "\tcompareFunction : " + to_string(p_compareFunction) + "\n";
	desc += "\trightType : " + to_string(p_rightType) + "\n";
	desc += "\trightParameter : " + to_string(p_rightParameter) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ConditionData*>* ConditionData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ConditionData*>();
		static string resPath = "res/base/data/condition.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ConditionData* conditionData = new ConditionData();
				conditionData->p_conditionId = buffer->getString();
				conditionData->p_leftType = buffer->getString();
				conditionData->p_leftParameter = buffer->getString();
				conditionData->p_compareFunction = buffer->getString();
				conditionData->p_rightType = buffer->getString();
				conditionData->p_rightParameter = buffer->getString();
				p_sharedDictionary->insert(pair<string, ConditionData*>(conditionData->p_conditionId, conditionData));
			}
		}
	}
	return p_sharedDictionary;
}

ConditionData* ConditionData::getConditionDataById(const string& conditionId)
{
	if (ConditionData::getSharedDictionary()->count(conditionId)) {
		return ConditionData::getSharedDictionary()->at(conditionId);
	}
	return nullptr;
}

string ConditionData::getFieldValue(const string & fieldName)
{
	if (fieldName == "conditionId") {
		return to_string(this->getConditionId());
	} else if (fieldName == "leftType") {
		return to_string(this->getLeftType());
	} else if (fieldName == "leftParameter") {
		return to_string(this->getLeftParameter());
	} else if (fieldName == "compareFunction") {
		return to_string(this->getCompareFunction());
	} else if (fieldName == "rightType") {
		return to_string(this->getRightType());
	} else if (fieldName == "rightParameter") {
		return to_string(this->getRightParameter());
	}
	CCLOGWARN("Couldn't recognize %s in ConditionData", fieldName.c_str());
	return "";
}

