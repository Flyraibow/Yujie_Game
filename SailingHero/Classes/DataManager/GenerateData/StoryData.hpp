/*
This file (StoryData.hpp) is generated
*/
#ifndef StoryData_hpp
#define StoryData_hpp
#include <map>
#include "BaseData.h"
#include "StoryEventData.hpp"
#include "HeroData.hpp"


class StoryData: public BaseData
{
private:
	static map<string, StoryData*>* p_sharedDictionary;
	string p_storyId;
	string p_storyEventId;
	string p_heroId;
	bool p_repeated;
	int p_priority;
public:
	string getId() const;
	string getStoryId() const;
	StoryEventData* getStoryEventData() const;
	string getStoryEventId() const;
	HeroData* getHeroData() const;
	string getHeroId() const;
	bool getRepeated() const;
	int getPriority() const;
	string description() const;
	static const map<string, StoryData*>* getSharedDictionary();
	static StoryData* getStoryDataById(const string& storyId);
	string getFieldValue(const string & fieldName);
};
#endif
