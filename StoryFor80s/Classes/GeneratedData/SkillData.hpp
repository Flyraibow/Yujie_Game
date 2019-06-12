/*
This file (SkillData.hpp) is generated
*/
#ifndef SkillData_hpp
#define SkillData_hpp
#include <map>
#include "BaseData.h"


class SkillData: public BaseData
{
private:
	static map<string, SkillData*>* p_sharedDictionary;
	string p_skillId;
	bool p_haveIt;
public:
	string getId() const;
	string getSkillId() const;
	bool getHaveIt() const;
	void setHaveIt(bool haveIt);
	string description() const;
	static const map<string, SkillData*>* getSharedDictionary();
	static SkillData* getSkillDataById(const string& skillId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
