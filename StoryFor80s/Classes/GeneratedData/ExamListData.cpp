/*
This file (ExamListData.cpp) is generated
*/
#include "ExamListData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace Utils;

map<string, ExamListData*>* ExamListData::p_sharedDictionary = nullptr;

string ExamListData::getId() const
{
	return to_string(p_examListId);
}

string ExamListData::getExamListId() const
{
	return p_examListId;
}

string ExamListData::getName() const
{
	string localId = "examList_name_" + to_string(p_examListId);
	return LocalizationHelper::getLocalization(localId);
}

int ExamListData::getPriority() const
{
	return p_priority;
}

string ExamListData::getCondition() const
{
	return p_condition;
}

SchoolData* ExamListData::getSchoolData() const
{
	return SchoolData::getSchoolDataById(p_schoolId);
}

string ExamListData::getSchoolId() const
{
	return p_schoolId;
}

int ExamListData::getYear() const
{
	return p_year;
}

int ExamListData::getMonth() const
{
	return p_month;
}

vector<ExamData*> ExamListData::getClassesDataVector() const
{
	vector<ExamData*> resultVector;
	for (auto objId : p_classesIdVector) {
		resultVector.push_back(ExamData::getExamDataById(objId));
	}
	return resultVector;
}

vector<string> ExamListData::getClassesIdVector() const
{
	return p_classesIdVector;
}

int ExamListData::getPopulation() const
{
	return p_population;
}

string ExamListData::description() const
{
	string desc = "examListData = {\n";
	desc += "\texamListId : " + to_string(p_examListId) + "\n";
	desc += "\tname : " + getName() + "\n";
	desc += "\tpriority : " + to_string(p_priority) + "\n";
	desc += "\tcondition : " + to_string(p_condition) + "\n";
	desc += "\tschool : " + to_string(p_schoolId) + "\n";
	desc += "\tyear : " + to_string(p_year) + "\n";
	desc += "\tmonth : " + to_string(p_month) + "\n";
	desc += "\tclasses : " + to_string(p_classesIdVector) + "\n";
	desc += "\tpopulation : " + to_string(p_population) + "\n";
	desc += "}\n";
	return desc;
}

const map<string, ExamListData*>* ExamListData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, ExamListData*>();
		static string resPath = "res/base/data/examList.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ExamListData* examListData = new ExamListData();
				examListData->p_examListId = buffer->getString();
				examListData->p_priority = buffer->getInt();
				examListData->p_condition = buffer->getString();
				examListData->p_schoolId = buffer->getString();
				examListData->p_year = buffer->getInt();
				examListData->p_month = buffer->getInt();
				auto classesCount = buffer->getLong();
				for (int j = 0; j < classesCount; ++j) {
					examListData->p_classesIdVector.push_back(buffer->getString());
				}
				examListData->p_population = buffer->getInt();
				p_sharedDictionary->insert(pair<string, ExamListData*>(examListData->p_examListId, examListData));
			}
		}
	}
	return p_sharedDictionary;
}

ExamListData* ExamListData::getExamListDataById(const string& examListId)
{
	if (ExamListData::getSharedDictionary()->count(examListId)) {
		return ExamListData::getSharedDictionary()->at(examListId);
	}
	return nullptr;
}

string ExamListData::getFieldValue(const string & fieldName) const
{
	if (fieldName == "examListId") {
		return to_string(this->getExamListId());
	} else if (fieldName == "name") {
		return to_string(this->getName());
	} else if (fieldName == "priority") {
		return to_string(this->getPriority());
	} else if (fieldName == "condition") {
		return to_string(this->getCondition());
	} else if (fieldName == "school") {
		return to_string(this->getSchoolId());
	} else if (fieldName == "year") {
		return to_string(this->getYear());
	} else if (fieldName == "month") {
		return to_string(this->getMonth());
	} else if (fieldName == "classes") {
		return to_string(this->getClassesIdVector());
	} else if (fieldName == "population") {
		return to_string(this->getPopulation());
	}
	CCLOGWARN("Couldn't recognize %s in ExamListData", fieldName.c_str());
	return "";
}

BaseData* ExamListData::getDataByField(const string & fieldName) const
{
	if (fieldName == "school") {
		return this->getSchoolData();
	}
	CCLOGWARN("Couldn't recognize %s in ExamListData", fieldName.c_str());
	return nullptr;
}

vector<BaseData *> ExamListData::getFieldDataList(const string & fieldName) const
{
	CCLOGWARN("Couldn't recognize %s in ExamListData", fieldName.c_str());
	return vector<BaseData *>();
}

