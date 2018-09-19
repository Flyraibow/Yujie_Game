/*
This file (ButtonData.hpp) is generated
*/
#ifndef ButtonData_hpp
#define ButtonData_hpp
#include <map>
#include "BaseData.h"
#include "ConditionData.hpp"
#include "EventData.hpp"


class ButtonData: public BaseData
{
private:
	static map<string, ButtonData*>* p_sharedDictionary;
	string p_buttonId;
	string p_conditionId;
	string p_triggerEventId;
public:
	string getId() const;
	string getButtonId() const;
	string getLabel() const;
	ConditionData* getConditionData() const;
	string getConditionId() const;
	EventData* getTriggerEventData() const;
	string getTriggerEventId() const;
	string description() const;
	static const map<string, ButtonData*>* getSharedDictionary();
	static ButtonData* getButtonDataById(const string& buttonId);
	string getFieldValue(const string & fieldName);
};
#endif
