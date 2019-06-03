/*
This file (BaseDataManager.hpp) is generated
*/
#ifndef BaseDataManager_hpp
#define BaseDataManager_hpp
#include "ConditionData.hpp"
#include "PlotData.hpp"
#include "ConditionCalculationData.hpp"
#include "FatherJobData.hpp"
#include "PlayData.hpp"
#include "StoryData.hpp"
#include "DateData.hpp"
#include "ItemData.hpp"
#include "ItemCategoryData.hpp"
#include "FriendData.hpp"
#include "ParentChatData.hpp"
#include "SelfStudyData.hpp"
#include "AttributeData.hpp"
#include "FunctionCalculationData.hpp"
#include "WorkData.hpp"
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
	static PlotData* getPlotDataById(const string& plotId);
	static ConditionCalculationData* getConditionCalculationDataById(const string& conditionCalculationId);
	static FatherJobData* getFatherJobDataById(const string& fatherJobId);
	static PlayData* getPlayDataById(const string& playId);
	static StoryData* getStoryDataById(const string& storyId);
	static DateData* getDateDataById(const string& dateId);
	static ItemData* getItemDataById(const string& itemId);
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
	static FriendData* getFriendDataById(const string& friendId);
	static ParentChatData* getParentChatDataById(const string& chatId);
	static SelfStudyData* getSelfStudyDataById(const string& selfStudyId);
	static AttributeData* getAttributeDataById(const string& attributeId);
	static FunctionCalculationData* getFunctionCalculationDataById(const string& functionCalculatonId);
	static WorkData* getWorkDataById(const string& actionId);
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
