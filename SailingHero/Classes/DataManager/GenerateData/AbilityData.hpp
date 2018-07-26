/*
This file (AbilityData.hpp) is generated
*/
#ifndef AbilityData_hpp
#define AbilityData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class AbilityData: public BaseData
{
private:
	static map<int, AbilityData*>* p_sharedDictionary;
	int p_abilityId;
public:
	string getId() const;
	int getAbilityId() const;
	string getAbilityName() const;
	string getAbilityDescription() const;
	string description() const;
	static map<int, AbilityData*>* getSharedDictionary();
	static AbilityData* getAbilityDataById(int abilityId);
	static AbilityData* getAbilityDataById(const string& abilityId);
};
#endif
