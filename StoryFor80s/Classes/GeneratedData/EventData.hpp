/*
This file (EventData.hpp) is generated
*/
#ifndef EventData_hpp
#define EventData_hpp
#include <map>
#include "BaseData.h"


class EventData: public BaseData
{
private:
	static map<string, EventData*>* p_sharedDictionary;
	string p_eventId;
	string p_type;
	map<string, string> p_parametrsMap;
public:
	string getId() const;
	string getEventId() const;
	string getType() const;
	map<string, string> getParametrsMap() const;
	string description() const;
	static const map<string, EventData*>* getSharedDictionary();
	static EventData* getEventDataById(const string& eventId);
	string getFieldValue(const string & fieldName);
};
#endif
