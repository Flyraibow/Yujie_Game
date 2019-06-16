/*
This file (BaseDataManager.hpp) is generated
*/
#ifndef BaseDataManager_hpp
#define BaseDataManager_hpp
#include "ConditionData.hpp"
#include "ExamData.hpp"
#include "PlotData.hpp"
#include "ConditionCalculationData.hpp"
#include "AchievementCategoryData.hpp"
#include "FatherJobData.hpp"
#include "ScheduleSubTypeData.hpp"
#include "StoryData.hpp"
#include "DateData.hpp"
#include "ScheduleTypeData.hpp"
#include "ItemData.hpp"
#include "MyScheduleData.hpp"
#include "ScheduleData.hpp"
#include "ExamListData.hpp"
#include "ProficiencyCategoryData.hpp"
#include "ItemCategoryData.hpp"
#include "FriendData.hpp"
#include "ParentChatData.hpp"
#include "TaskData.hpp"
#include "SkillData.hpp"
#include "AttributeData.hpp"
#include "SelectableScheduleData.hpp"
#include "AchievementsData.hpp"
#include "FunctionCalculationData.hpp"
#include "SchoolStudyData.hpp"
#include "ActionData.hpp"
#include "GameData.hpp"
#include "SchoolData.hpp"
#include "ProficiencyData.hpp"


class BaseDataManager
{
private:
public:
	static ConditionData* getConditionDataById(const string& conditionId);
	static ExamData* getExamDataById(const string& examId);
	static PlotData* getPlotDataById(const string& plotId);
	static ConditionCalculationData* getConditionCalculationDataById(const string& conditionCalculationId);
	static AchievementCategoryData* getAchievementCategoryDataById(const string& categoryId);
	static FatherJobData* getFatherJobDataById(const string& fatherJobId);
	static ScheduleSubTypeData* getScheduleSubTypeDataById(const string& scheduleSubTypeId);
	static StoryData* getStoryDataById(const string& storyId);
	static DateData* getDateDataById(const string& dateId);
	static ScheduleTypeData* getScheduleTypeDataById(const string& scheduleTypeId);
	static ItemData* getItemDataById(const string& itemId);
	static MyScheduleData* getMyScheduleDataById(const string& myScheduleId);
	static ScheduleData* getScheduleDataById(const string& scheduleId);
	static ExamListData* getExamListDataById(const string& examListId);
	static ProficiencyCategoryData* getProficiencyCategoryDataById(const string& proficiencyCategoryId);
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
	static FriendData* getFriendDataById(const string& friendId);
	static ParentChatData* getParentChatDataById(const string& chatId);
	static TaskData* getTaskDataById(const string& itemId);
	static SkillData* getSkillDataById(const string& skillId);
	static AttributeData* getAttributeDataById(const string& attributeId);
	static SelectableScheduleData* getSelectableScheduleDataById(const string& scheduleId);
	static AchievementsData* getAchievementsDataById(const string& achievementId);
	static FunctionCalculationData* getFunctionCalculationDataById(const string& functionCalculatonId);
	static SchoolStudyData* getSchoolStudyDataById(const string& schoolStudyId);
	static ActionData* getActionDataById(const string& actionId);
	static GameData* getGameData();
	static SchoolData* getSchoolDataById(const string& schoolId);
	static ProficiencyData* getProficiencyDataById(const string& proficiencyId);
	static bool saveData(string fileName);
	static bool loadData(string fileName);
	static bool clearData();
	static BaseData * getData(const string & dataSet, const string & id);
	static string getDataField(const string & dataSet, const string & id, const string & fieldName);
	static void setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value);
	static vector<BaseData *> getDataList(const string & dataSet);
};
#endif
