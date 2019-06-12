/*
This file (AchievementsData.hpp) is generated
*/
#ifndef AchievementsData_hpp
#define AchievementsData_hpp
#include <map>
#include "BaseData.h"
#include "AchievementCategoryData.hpp"


class AchievementsData: public BaseData
{
private:
	static map<string, AchievementsData*>* p_sharedDictionary;
	string p_achievementId;
	string p_categoryId;
	int p_value;
	int p_validUntilYear;
	int p_validUntilMonth;
	bool p_haveIt;
public:
	string getId() const;
	string getAchievementId() const;
	string getName() const;
	AchievementCategoryData* getCategoryData() const;
	string getCategoryId() const;
	int getValue() const;
	int getValidUntilYear() const;
	int getValidUntilMonth() const;
	bool getHaveIt() const;
	void setHaveIt(bool haveIt);
	string description() const;
	static const map<string, AchievementsData*>* getSharedDictionary();
	static AchievementsData* getAchievementsDataById(const string& achievementId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
