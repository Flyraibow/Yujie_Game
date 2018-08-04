/*
This file (CityStatusData.hpp) is generated
*/
#ifndef CityStatusData_hpp
#define CityStatusData_hpp
#include <map>
#include "BaseData.h"


enum class CITY_STATUS
{
	NORMAL = 0,
	GOOD = 1,
	BAD = 2,
	WAR = 3,
	HUNGRY = 4,
	ILLNESS = 5,
};

class CityStatusData: public BaseData
{
private:
	static map<int, CityStatusData*>* p_sharedDictionary;
	int p_cityStatusId;
public:
	string getId() const;
	int getCityStatusId() const;
	string getCityStatusName() const;
	string description() const;
	static const map<int, CityStatusData*>* getSharedDictionary();
	static CityStatusData* getCityStatusDataById(int cityStatusId);
	static CityStatusData* getCityStatusDataById(const string& cityStatusId);
};
#endif
