/*
This file (SystemButtonData.hpp) is generated
*/
#ifndef SystemButtonData_hpp
#define SystemButtonData_hpp
#include <map>
#include "BaseData.h"
#include "EventData.hpp"


class SystemButtonData: public BaseData
{
private:
	static map<int, SystemButtonData*>* p_sharedDictionary;
	int p_buttonId;
	string p_eventId;
public:
	string getId() const;
	int getButtonId() const;
	string getButtonName() const;
	EventData* getEventData() const;
	string getEventId() const;
	virtual string description() const;
	static const map<int, SystemButtonData*>* getSharedDictionary();
	static SystemButtonData* getSystemButtonDataById(int buttonId);
	static SystemButtonData* getSystemButtonDataById(const string& buttonId);
	string getFieldValue(const string & fieldName);
};
#endif
