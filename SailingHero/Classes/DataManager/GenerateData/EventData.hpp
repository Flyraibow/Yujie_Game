/*
This file (EventData.hpp) is generated
*/
#ifndef EventData_hpp
#define EventData_hpp
#include <map>
#include "BaseData.h"
#include <vector>


class EventData: public BaseData
{
private:
	static map<string, EventData*>* p_sharedDictionary;
	string p_eventId;
	string p_eventType;
	vector<string> p_parameters;
public:
	string getId() const;
	string getEventId() const;
	string getEventType() const;
	vector<string> getParameters() const;
	string description() const;
	static const map<string, EventData*>* getSharedDictionary();
	static EventData* getEventDataById(const string& eventId);
	string getFieldValue(const string & fieldName);
};
#endif
