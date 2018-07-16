/*
This file (GenderData.hpp) is generated
*/
#ifndef GenderData_hpp
#define GenderData_hpp
#include <map>
#include "BaseData.h"

using namespace std;
class GenderData: public BaseData
{
private:
	static map<string, GenderData*>* p_sharedDictionary;
	string p_genderId;
public:
	string getId() const;
	string getGenderId() const;
	string getGenderName() const;
	string description() const;
	static map<string, GenderData*>* getSharedDictionary();
	static GenderData* getGenderDataById(const string& genderId);
};
#endif
