/*
This file (CityBuildingData.hpp) is generated
*/
#ifndef CityBuildingData_hpp
#define CityBuildingData_hpp
#include <map>
#include "BaseData.h"

using namespace std;
class CityBuildingData: public BaseData
{
private:
	static map<int, CityBuildingData*>* p_sharedDictionary;
	int p_buildingId;
	string p_buildingImage;
public:
	string getId() const;
	int getBuildingId() const;
	string getBuildingName() const;
	string getBuildingImage() const;
	string description() const;
	static map<int, CityBuildingData*>* getSharedDictionary();
	static CityBuildingData* getCityBuildingDataById(int buildingId);
	static CityBuildingData* getCityBuildingDataById(const string& buildingId);
};
#endif
