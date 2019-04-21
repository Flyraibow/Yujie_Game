/*
This file (StudyData.hpp) is generated
*/
#ifndef StudyData_hpp
#define StudyData_hpp
#include <map>
#include "BaseData.h"
#include <set>
#include "StudyData.hpp"
#include "AttributeData.hpp"
#include "AttributeData.hpp"


class StudyData: public BaseData
{
private:
	static map<string, StudyData*>* p_sharedDictionary;
	string p_studyId;
	string p_studyCondition;
	int p_maxValue;
	int p_passValue;
	int p_value;
	set<string> p_requiresIdSet;
	map<string, int> p_schoolAttributeChangeMap;
	map<string, int> p_selfstudyAttributeChangeMap;
public:
	string getId() const;
	string getStudyId() const;
	string getName() const;
	string getStudyCondition() const;
	int getMaxValue() const;
	int getPassValue() const;
	int getValue() const;
	void setValue(int value);
	set<StudyData*> getRequiresDataSet() const;
	set<string> getRequiresIdSet() const;
	string getDescription() const;
	vector<BaseData *> getSchoolAttributeChangeList() const;
	map<string, int> getSchoolAttributeChangeMap() const;
	vector<BaseData *> getSelfstudyAttributeChangeList() const;
	map<string, int> getSelfstudyAttributeChangeMap() const;
	string description() const;
	static const map<string, StudyData*>* getSharedDictionary();
	static StudyData* getStudyDataById(const string& studyId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
	string getMapFieldValueWithKey(const string & fieldName, const string & key) const;
};
#endif
