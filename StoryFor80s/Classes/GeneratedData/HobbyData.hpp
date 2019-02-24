/*
This file (HobbyData.hpp) is generated
*/
#ifndef HobbyData_hpp
#define HobbyData_hpp
#include <map>
#include "BaseData.h"


class HobbyData: public BaseData
{
private:
	static map<string, HobbyData*>* p_sharedDictionary;
	string p_hobbyId;
	int p_expense;
	int p_proficiency;
public:
	string getId() const;
	string getHobbyId() const;
	string getName() const;
	int getExpense() const;
	int getProficiency() const;
	void setProficiency(int proficiency);
	string description() const;
	static const map<string, HobbyData*>* getSharedDictionary();
	static HobbyData* getHobbyDataById(const string& hobbyId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
