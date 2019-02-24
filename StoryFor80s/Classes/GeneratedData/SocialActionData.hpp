/*
This file (SocialActionData.hpp) is generated
*/
#ifndef SocialActionData_hpp
#define SocialActionData_hpp
#include <map>
#include "BaseData.h"
#include "EventData.hpp"


class SocialActionData: public BaseData
{
private:
	static map<string, SocialActionData*>* p_sharedDictionary;
	string p_socialActionId;
	string p_eventId;
public:
	string getId() const;
	string getSocialActionId() const;
	string getName() const;
	EventData* getEventData() const;
	string getEventId() const;
	string description() const;
	static const map<string, SocialActionData*>* getSharedDictionary();
	static SocialActionData* getSocialActionDataById(const string& socialActionId);
	string getFieldValue(const string & fieldName);
};
#endif
