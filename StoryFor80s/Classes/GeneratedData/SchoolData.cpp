/*
This file (SchoolData.cpp) is generated
*/
#include "SchoolData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, SchoolData*>* SchoolData::p_sharedDictionary = nullptr;

string SchoolData::getId() const
{
	return to_string(p_schoolId);
}

string SchoolData::getSchoolId() const
{
	return p_schoolId;
}

string SchoolData::getName() const
{
	string localId = "school_name_" + to_string(p_schoolId);
	return LocalizationHelper::getLocalization(localId);
}

float SchoolData::getStudyFactor() const
{
	return p_studyFactor;
}

string SchoolData::description() const
{
	string desc = "schoolData = {\n";
	desc += "\tschoolId : " + to_string(p_schoolId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tstudyFactor : " + to_string(p_studyFactor) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, SchoolData*>* SchoolData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, SchoolData*>();
		static string resPath = "res/base/data/school.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				SchoolData* schoolData = new SchoolData();
				schoolData->p_schoolId = buffer->getString();
				schoolData->p_studyFactor = buffer->getFloat();
				p_sharedDictionary->insert(pair<string, SchoolData*>(schoolData->p_schoolId, schoolData));
			}
		}
	}
	return p_sharedDictionary;
}

SchoolData* SchoolData::getSchoolDataById(const string& schoolId)
{
	if (SchoolData::getSharedDictionary()->count(schoolId)) {
		return SchoolData::getSharedDictionary()->at(schoolId);
	}
	return nullptr;
}

string SchoolData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "schoolId") {
		return to_string(this->getSchoolId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "studyFactor") {
		return to_string(this->getStudyFactor());
	}
	CCLOGWARN("Couldn't recognize %s in SchoolData", fieldName.c_str());
	return "";
}

BaseData* SchoolData::getDataByField(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in SchoolData", fieldName.c_str());
	return nullptr;
}

