/*
This file (StoryData.hpp) is generated
*/
#ifndef StoryData_hpp
#define StoryData_hpp
#include <map>
#include "BaseData.h"


class StoryData: public BaseData
{
private:
	static map<string, StoryData*>* p_sharedDictionary;
	string p_storyId;
	string p_storyEvent;
	int p_year;
	int p_month;
	bool p_once;
	int p_count;
public:
	string getId() const;
	string getStoryId() const;
	string getStoryEvent() const;
	int getYear() const;
	int getMonth() const;
	bool getOnce() const;
	int getCount() const;
	void setCount(int count);
	string description() const;
	static const map<string, StoryData*>* getSharedDictionary();
	static StoryData* getStoryDataById(const string& storyId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
