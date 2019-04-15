/*
This file (FunctionCalculationData.cpp) is generated
*/
#include "FunctionCalculationData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"


using namespace Utils;

map<string, FunctionCalculationData*>* FunctionCalculationData::p_sharedDictionary = nullptr;

string FunctionCalculationData::getId() const
{
	return to_string(p_functionCalculatonId);
}

string FunctionCalculationData::getFunctionCalculatonId() const
{
	return p_functionCalculatonId;
}

string FunctionCalculationData::getReturnType() const
{
	return p_returnType;
}

string FunctionCalculationData::getFunctionName() const
{
	return p_functionName;
}

vector<string> FunctionCalculationData::getParameters() const
{
	return p_parameters;
}

string FunctionCalculationData::description() const
{
	string desc = "functionCalculationData = {\n";
	desc += "\tfunctionCalculatonId : " + to_string(p_functionCalculatonId) + "\n";
	desc += "\treturnType : " + to_string(p_returnType) + "\n";
	desc += "\tfunctionName : " + to_string(p_functionName) + "\n";
	desc += "\tparameters : " + to_string(p_parameters) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, FunctionCalculationData*>* FunctionCalculationData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, FunctionCalculationData*>();
		static string resPath = "res/base/data/functionCalculation.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				FunctionCalculationData* functionCalculationData = new FunctionCalculationData();
				functionCalculationData->p_functionCalculatonId = buffer->getString();
				functionCalculationData->p_returnType = buffer->getString();
				functionCalculationData->p_functionName = buffer->getString();
				auto parametersCount = buffer->getLong();
				for (int j = 0; j < parametersCount; ++j) {
					functionCalculationData->p_parameters.push_back(buffer->getString());
				}
				p_sharedDictionary->insert(pair<string, FunctionCalculationData*>(functionCalculationData->p_functionCalculatonId, functionCalculationData));
			}
		}
	}
	return p_sharedDictionary;
}

FunctionCalculationData* FunctionCalculationData::getFunctionCalculationDataById(const string& functionCalculatonId)
{
	if (FunctionCalculationData::getSharedDictionary()->count(functionCalculatonId)) {
		return FunctionCalculationData::getSharedDictionary()->at(functionCalculatonId);
	}
	return nullptr;
}

string FunctionCalculationData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "functionCalculatonId") {
		return to_string(this->getFunctionCalculatonId());
	} else if (fieldName == "returnType") {
		return to_string(this->getReturnType());
	} else if (fieldName == "functionName") {
		return to_string(this->getFunctionName());
	} else if (fieldName == "parameters") {
		return to_string(this->getParameters());
	}
	CCLOGWARN("Couldn't recognize %s in FunctionCalculationData", fieldName.c_str());
	return "";
}

BaseData* FunctionCalculationData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in FunctionCalculationData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> FunctionCalculationData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in FunctionCalculationData", fieldName.c_str());
	return vector<BaseData *>();
}

