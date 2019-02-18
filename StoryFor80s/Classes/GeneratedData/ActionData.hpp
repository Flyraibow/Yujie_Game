/*
This file (ActionData.hpp) is generated
*/
#ifndef ActionData_hpp
#define ActionData_hpp
#include <map>
#include "BaseData.h"
#include "EventData.hpp"


class ActionData: public BaseData
{
private:
	static map<string, ActionData*>* p_sharedDictionary;
	string p_actionId;
	string p_eventId;
public:
	string getId() const;
	string getActionId() const;
	string getName() const;
	EventData* getEventData() const;
	string getEventId() const;
	string description() const;
	static const map<string, ActionData*>* getSharedDictionary();
	static ActionData* getActionDataById(const string& actionId);
	string getFieldValue(const string & fieldName);
};
#endif
