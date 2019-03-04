/*
This file (BaseDataManager.hpp) is generated
*/
#ifndef BaseDataManager_hpp
#define BaseDataManager_hpp
#include "ConditionData.hpp"
#include "ConditionCalculationData.hpp"
#include "HobbyData.hpp"
#include "FatherJobData.hpp"
#include "StoryData.hpp"
#include "SkillsData.hpp"
#include "SocialActionData.hpp"
#include "ItemData.hpp"
#include "ItemCategoryData.hpp"
#include "FriendData.hpp"
#include "ParentChatData.hpp"
#include "AttributeData.hpp"
#include "FunctionCalculationData.hpp"
#include "WorkData.hpp"
#include "ActionData.hpp"
#include "GameData.hpp"


class BaseDataManager
{
private:
public:
	static ConditionData* getConditionDataById(const string& conditionId);
	static ConditionCalculationData* getConditionCalculationDataById(const string& conditionCalculationId);
	static HobbyData* getHobbyDataById(const string& hobbyId);
	static FatherJobData* getFatherJobDataById(const string& fatherJobId);
	static StoryData* getStoryDataById(const string& storyId);
	static SkillsData* getSkillsDataById(const string& skillId);
	static SocialActionData* getSocialActionDataById(const string& socialActionId);
	static ItemData* getItemDataById(const string& itemId);
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
	static FriendData* getFriendDataById(const string& friendId);
	static ParentChatData* getParentChatDataById(const string& chatId);
	static AttributeData* getAttributeDataById(const string& attributeId);
	static FunctionCalculationData* getFunctionCalculationDataById(const string& functionCalculatonId);
	static WorkData* getWorkDataById(const string& actionId);
	static ActionData* getActionDataById(const string& actionId);
	static GameData* getGameData();
	static bool saveData(string fileName);
	static bool loadData(string fileName);
	static bool clearData();
	static BaseData * getData(const string & dataSet, const string & id);
	static string getDataField(const string & dataSet, const string & id, const string & fieldName);
	static void setDataField(const string & dataSet, const string & id, const string & fieldName, const string & value);
};
#endif
