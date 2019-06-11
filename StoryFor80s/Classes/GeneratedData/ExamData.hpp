/*
This file (ExamData.hpp) is generated
*/
#ifndef ExamData_hpp
#define ExamData_hpp
#include <map>
#include "BaseData.h"
#include "ProficiencyData.hpp"
#include "ProficiencyData.hpp"
#include "ProficiencyData.hpp"
#include "AttributeData.hpp"


class ExamData: public BaseData
{
private:
	static map<string, ExamData*>* p_sharedDictionary;
	string p_examId;
	int p_baseValue;
	map<string, int> p_baseProficiencyRequirementsMap;
	int p_midValue;
	map<string, int> p_midProficiencyRequirementsMap;
	int p_highValue;
	map<string, int> p_highProficiencyRequirementsMap;
	map<string, int> p_highAttributeRequirementsMap;
	int p_lowestScore;
	int p_midScore;
	int p_highestScore;
public:
	string getId() const;
	string getExamId() const;
	string getName() const;
	int getBaseValue() const;
	vector<BaseData *> getBaseProficiencyRequirementsList() const;
	map<string, int> getBaseProficiencyRequirementsMap() const;
	int getMidValue() const;
	vector<BaseData *> getMidProficiencyRequirementsList() const;
	map<string, int> getMidProficiencyRequirementsMap() const;
	int getHighValue() const;
	vector<BaseData *> getHighProficiencyRequirementsList() const;
	map<string, int> getHighProficiencyRequirementsMap() const;
	vector<BaseData *> getHighAttributeRequirementsList() const;
	map<string, int> getHighAttributeRequirementsMap() const;
	int getLowestScore() const;
	int getMidScore() const;
	int getHighestScore() const;
	string description() const;
	static const map<string, ExamData*>* getSharedDictionary();
	static ExamData* getExamDataById(const string& examId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
