/*
This file (ExamListData.hpp) is generated
*/
#ifndef ExamListData_hpp
#define ExamListData_hpp
#include <map>
#include "BaseData.h"
#include <vector>
#include "SchoolData.hpp"
#include "ExamData.hpp"
#include "AchievementsData.hpp"
#include "AchievementsData.hpp"


class ExamListData: public BaseData
{
private:
	static map<string, ExamListData*>* p_sharedDictionary;
	string p_examListId;
	int p_priority;
	string p_condition;
	string p_schoolId;
	int p_year;
	int p_month;
	vector<string> p_classesIdVector;
	int p_population;
	string p_rankAchievementId;
	string p_scoreAchievementId;
	int p_achievementNeedScore;
public:
	string getId() const;
	string getExamListId() const;
	string getName() const;
	int getPriority() const;
	string getCondition() const;
	SchoolData* getSchoolData() const;
	string getSchoolId() const;
	int getYear() const;
	int getMonth() const;
	vector<ExamData*> getClassesDataVector() const;
	vector<string> getClassesIdVector() const;
	int getPopulation() const;
	AchievementsData* getRankAchievementData() const;
	string getRankAchievementId() const;
	AchievementsData* getScoreAchievementData() const;
	string getScoreAchievementId() const;
	int getAchievementNeedScore() const;
	string description() const;
	static const map<string, ExamListData*>* getSharedDictionary();
	static ExamListData* getExamListDataById(const string& examListId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
