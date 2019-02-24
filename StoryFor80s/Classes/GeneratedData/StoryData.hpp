/*
This file (StoryData.hpp) is generated
*/
#ifndef StoryData_hpp
#define StoryData_hpp
#include <map>
#include "BaseData.h"
#include "ConditionData.hpp"


class StoryData: public BaseData
{
private:
	static map<string, StoryData*>* p_sharedDictionary;
	string p_storyId;
	string p_storyEvent;
	bool p_once;
	int p_count;
	string p_conditionId;
public:
	string getId() const;
	string getStoryId() const;
	string getStoryEvent() const;
	bool getOnce() const;
	int getCount() const;
	void setCount(int count);
	ConditionData* getConditionData() const;
	string getConditionId() const;
	string description() const;
	static const map<string, StoryData*>* getSharedDictionary();
	static StoryData* getStoryDataById(const string& storyId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
