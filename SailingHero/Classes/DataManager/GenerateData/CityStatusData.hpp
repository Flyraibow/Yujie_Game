/*
This file (CityStatusData.hpp) is generated
*/
#ifndef CityStatusData_hpp
#define CityStatusData_hpp
#include <map>
#include "BaseData.h"

using namespace std;
class CityStatusData: public BaseData
{
private:
	static map<string, CityStatusData*>* p_sharedDictionary;
	string p_cityStatusId;
public:
	string getId() const;
	string getCityStatusId() const;
	string getCityStatusName() const;
	string description() const;
	static map<string, CityStatusData*>* getSharedDictionary();
	static CityStatusData* getCityStatusDataById(const string& cityStatusId);
};
#endif
