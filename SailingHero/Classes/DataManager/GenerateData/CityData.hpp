/*
This file (CityData.hpp) is generated
*/
#ifndef CityData_hpp
#define CityData_hpp
#include <map>
#include "BaseData.h"
#include <set>
#include <vector>
#include "CultureData.hpp"
#include "CityTypeData.hpp"
#include "CityGoodsData.hpp"
#include "CityBuildingData.hpp"

using namespace std;
class CityData: public BaseData
{
private:
	static map<string, CityData*>* p_sharedDictionary;
	string p_cityId;
	string p_cityName;
	string p_cultureId;
	string p_cityTypeId;
	double p_longitude;
	double p_latitude;
	int p_commerce;
	int p_milltary;
	vector<string> p_cityGoodsIdVector;
	set<string> p_buildingIdSet;
public:
	string getId() const;
	string getCityId() const;
	void setCityName(string cityName);
	string getCityName() const;
	CultureData* getCultureData() const;
	string getCultureId() const;
	CityTypeData* getCityTypeData() const;
	string getCityTypeId() const;
	double getLongitude() const;
	double getLatitude() const;
	int getCommerce() const;
	void setCommerce(int commerce);
	int getMilltary() const;
	void setMilltary(int milltary);
	vector<CityGoodsData*> getCityGoodsDataVector() const;
	vector<string> getCityGoodsIdVector() const;
	set<CityBuildingData*> getBuildingDataSet() const;
	set<string> getBuildingIdSet() const;
	void setBuilding(set<string> building);
	string description() const;
	static map<string, CityData*>* getSharedDictionary();
	static CityData* getCityDataById(const string& cityId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
};
#endif
