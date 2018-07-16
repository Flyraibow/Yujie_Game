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
	static map<string, CityBuildingData*>* p_sharedDictionary;
	string p_buildingId;
	string p_buildingImage;
public:
	string getId() const;
	string getBuildingId() const;
	string getBuildingName() const;
	string getBuildingImage() const;
	string description() const;
	static map<string, CityBuildingData*>* getSharedDictionary();
	static CityBuildingData* getCityBuildingDataById(const string& buildingId);
};
#endif
