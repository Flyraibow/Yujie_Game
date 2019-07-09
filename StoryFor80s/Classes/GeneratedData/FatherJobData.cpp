/*
This file (FatherJobData.cpp) is generated
*/
#include "FatherJobData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, FatherJobData*>* FatherJobData::p_sharedDictionary = nullptr;

string FatherJobData::getId() const
{
	return to_string(p_fatherJobId);
}

string FatherJobData::getFatherJobId() const
{
	return p_fatherJobId;
}

string FatherJobData::getName() const
{
	string localId = "fatherJob_name_" + to_string(p_fatherJobId);
	return LocalizationHelper::getLocalization(localId);
}

bool FatherJobData::getSelecatable() const
{
	return p_selecatable;
}

int FatherJobData::getPoint() const
{
	return p_point;
}

int FatherJobData::getSalary() const
{
	return p_salary;
}

string FatherJobData::getDescription() const
{
	string localId = "fatherJob_description_" + to_string(p_fatherJobId);
	return LocalizationHelper::getLocalization(localId);
}

string FatherJobData::description() const
{
	string desc = "fatherJobData = {\n";
	desc += "\tfatherJobId : " + to_string(p_fatherJobId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tselecatable : " + to_string(p_selecatable) + "\n";
	desc += "\tpoint : " + to_string(p_point) + "\n";
	desc += "\tsalary : " + to_string(p_salary) + "\n";
	desc += "\tdescription : " + getDescription() + "\n";
	desc += "}\n";
	return desc;
}

const map<string, FatherJobData*>* FatherJobData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, FatherJobData*>();
		static string resPath = "res/base/data/fatherJob.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				FatherJobData* fatherJobData = new FatherJobData();
				fatherJobData->p_fatherJobId = buffer->getString();
				fatherJobData->p_selecatable = buffer->getChar();
				fatherJobData->p_point = buffer->getInt();
				fatherJobData->p_salary = buffer->getInt();
				p_sharedDictionary->insert(pair<string, FatherJobData*>(fatherJobData->p_fatherJobId, fatherJobData));
			}
		}
	}
	return p_sharedDictionary;
}

FatherJobData* FatherJobData::getFatherJobDataById(const string& fatherJobId)
{
	if (FatherJobData::getSharedDictionary()->count(fatherJobId)) {
		return FatherJobData::getSharedDictionary()->at(fatherJobId);
	}
	return nullptr;
}

string FatherJobData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "fatherJobId") {
		return to_string(this->getFatherJobId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "selecatable") {
		return to_string(this->getSelecatable());
	} else if (fieldName == "point") {
		return to_string(this->getPoint());
	} else if (fieldName == "salary") {
		return to_string(this->getSalary());
	} else if (fieldName == "description") {
		return to_string(this->getDescription());
	}
	CCLOGWARN("Couldn't recognize %s in FatherJobData", fieldName.c_str());
	return "";
}

BaseData* FatherJobData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in FatherJobData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> FatherJobData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in FatherJobData", fieldName.c_str());
	return vector<BaseData *>();
}

