/*
This file (ActionData.hpp) is generated
*/
#ifndef ActionData_hpp
#define ActionData_hpp
#include <map>
#include "BaseData.h"


class ActionData: public BaseData
{
private:
	static map<string, ActionData*>* p_sharedDictionary;
	string p_actionId;
public:
	string getId() const;
	string getActionId() const;
	string getName() const;
	string description() const;
	static const map<string, ActionData*>* getSharedDictionary();
	static ActionData* getActionDataById(const string& actionId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
};
#endif
