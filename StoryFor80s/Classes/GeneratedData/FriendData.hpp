/*
This file (FriendData.hpp) is generated
*/
#ifndef FriendData_hpp
#define FriendData_hpp
#include <map>
#include "BaseData.h"


class FriendData: public BaseData
{
private:
	static map<string, FriendData*>* p_sharedDictionary;
	string p_friendId;
	int p_birthMonth;
	int p_birthDay;
	int p_gender;
	int p_relation;
public:
	string getId() const;
	string getFriendId() const;
	string getLastName() const;
	string getFirstName() const;
	int getBirthMonth() const;
	int getBirthDay() const;
	int getGender() const;
	int getRelation() const;
	void setRelation(int relation);
	string description() const;
	static const map<string, FriendData*>* getSharedDictionary();
	static FriendData* getFriendDataById(const string& friendId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
	BaseData* getDataByField(const string & fieldName);
};
#endif
