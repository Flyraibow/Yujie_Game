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
	static map<int, CityTypeData*>* p_sharedDictionary;
	int p_cityTypeId;
public:
	string getId() const;
	int getCityTypeId() const;
	string getCityTypeName() const;
	string description() const;
	static map<int, CityTypeData*>* getSharedDictionary();
	static CityTypeData* getCityTypeDataById(int cityTypeId);
	static CityTypeData* getCityTypeDataById(const string& cityTypeId);
};
#endif
