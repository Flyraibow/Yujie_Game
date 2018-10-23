/*
This file (StoryEventData.hpp) is generated
*/
#ifndef StoryEventData_hpp
#define StoryEventData_hpp
#include <map>
#include "BaseData.h"
#include "StoryEventData.hpp"


class StoryEventData: public BaseData
{
private:
	static map<string, StoryEventData*>* p_sharedDictionary;
	string p_storyEventId;
	string p_type;
	double p_duration;
	string p_name;
	string p_path;
	map<string, string> p_parametrsMap;
	string p_nextStoryId;
public:
	string getId() const;
	string getStoryEventId() const;
	string getType() const;
	double getDuration() const;
	string getName() const;
	string getPath() const;
	map<string, string> getParametrsMap() const;
	StoryEventData* getNextStoryData() const;
	string getNextStoryId() const;
	string description() const;
	static const map<string, StoryEventData*>* getSharedDictionary();
	static StoryEventData* getStoryEventDataById(const string& storyEventId);
	string getFieldValue(const string & fieldName);
};
#endif
