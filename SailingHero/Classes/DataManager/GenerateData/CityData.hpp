/*
This file (CityData.hpp) is generated
*/
#ifndef CityData_hpp
#define CityData_hpp
#include <map>
#include "BaseData.h"
#include <set>
#include <vector>
#include "AreaData.hpp"
#include "CultureData.hpp"
#include "CityStatusData.hpp"
#include "TownPhotoData.hpp"
#include "CityTypeData.hpp"
#include "GuildData.hpp"
#include "CityGoodsData.hpp"
#include "CityBuildingData.hpp"


class CityData: public BaseData
{
private:
	static map<int, CityData*>* p_sharedDictionary;
	int p_cityId;
	string p_cityName;
	string p_areaId;
	string p_cultureId;
	string p_cityStatusId;
	string p_backGroundId;
	string p_cityTypeId;
	double p_longitude;
	double p_latitude;
	int p_commerce;
	int p_military;
	map<string, int> p_guildShareMap;
	vector<string> p_cityGoodsIdVector;
	set<string> p_buildingIdSet;
public:
	string getId() const;
	int getCityId() const;
	void setCityName(string cityName);
	string getCityName() const;
	AreaData* getAreaData() const;
	string getAreaId() const;
	CultureData* getCultureData() const;
	string getCultureId() const;
	CityStatusData* getCityStatusData() const;
	string getCityStatusId() const;
	void setCityStatusId(string cityStatus);
	TownPhotoData* getBackGroundData() const;
	string getBackGroundId() const;
	void setBackGroundId(string backGround);
	CityTypeData* getCityTypeData() const;
	string getCityTypeId() const;
	double getLongitude() const;
	double getLatitude() const;
	int getCommerce() const;
	void setCommerce(int commerce);
	int getMilitary() const;
	void setMilitary(int military);
	map<string, int> getGuildShareMap() const;
	void setGuildShareMap(map<string, int> guildShare);
	vector<CityGoodsData*> getCityGoodsDataVector() const;
	vector<string> getCityGoodsIdVector() const;
	set<CityBuildingData*> getBuildingDataSet() const;
	set<string> getBuildingIdSet() const;
	void setBuildingIdSet(set<string> building);
	string description() const;
	static const map<int, CityData*>* getSharedDictionary();
	static CityData* getCityDataById(int cityId);
	static CityData* getCityDataById(const string& cityId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
