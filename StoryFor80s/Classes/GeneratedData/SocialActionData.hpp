/*
This file (SocialActionData.hpp) is generated
*/
#ifndef SocialActionData_hpp
#define SocialActionData_hpp
#include <map>
#include "BaseData.h"


class SocialActionData: public BaseData
{
private:
	static map<string, SocialActionData*>* p_sharedDictionary;
	string p_socialActionId;
public:
	string getId() const;
	string getSocialActionId() const;
	string getName() const;
	string description() const;
	static const map<string, SocialActionData*>* getSharedDictionary();
	static SocialActionData* getSocialActionDataById(const string& socialActionId);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
