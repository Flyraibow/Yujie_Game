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
	static map<int, GenderData*>* p_sharedDictionary;
	int p_genderId;
public:
	string getId() const;
	int getGenderId() const;
	string getGenderName() const;
	string description() const;
	static map<int, GenderData*>* getSharedDictionary();
	static GenderData* getGenderDataById(int genderId);
	static GenderData* getGenderDataById(const string& genderId);
};
#endif
