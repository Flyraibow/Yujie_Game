/*
This file (CityTypeData.hpp) is generated
*/
#ifndef CityTypeData_hpp
#define CityTypeData_hpp
#include <map>
#include "BaseData.h"

using namespace std;
class CityTypeData: public BaseData
{
private:
	static map<string, CityTypeData*>* p_sharedDictionary;
	string p_cityTypeId;
public:
	string getId() const;
	string getCityTypeId() const;
	string getCityTypeName() const;
	string description() const;
	static map<string, CityTypeData*>* getSharedDictionary();
	static CityTypeData* getCityTypeDataById(const string& cityTypeId);
};
#endif
