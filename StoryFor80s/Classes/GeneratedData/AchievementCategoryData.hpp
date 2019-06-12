/*
This file (AchievementCategoryData.hpp) is generated
*/
#ifndef AchievementCategoryData_hpp
#define AchievementCategoryData_hpp
#include <map>
#include "BaseData.h"
#include <vector>
#include "AchievementCategoryData.hpp"


class AchievementCategoryData: public BaseData
{
private:
	static map<string, AchievementCategoryData*>* p_sharedDictionary;
	string p_categoryId;
	vector<string> p_subCategoryIdVector;
public:
	string getId() const;
	string getCategoryId() const;
	string getName() const;
	vector<AchievementCategoryData*> getSubCategoryDataVector() const;
	vector<string> getSubCategoryIdVector() const;
	string description() const;
	static const map<string, AchievementCategoryData*>* getSharedDictionary();
	static AchievementCategoryData* getAchievementCategoryDataById(const string& categoryId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
