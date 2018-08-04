/*
This file (CityBuildingData.hpp) is generated
*/
#ifndef CityBuildingData_hpp
#define CityBuildingData_hpp
#include <map>
#include "BaseData.h"


class CityBuildingData: public BaseData
{
private:
	static map<int, CityBuildingData*>* p_sharedDictionary;
	int p_buildingId;
	string p_buildingImageId;
	double p_anchorX;
	double p_anchorY;
	double p_posX;
	double p_posY;
public:
	string getId() const;
	int getBuildingId() const;
	string getBuildingName() const;
	cocos2d::Sprite* getBuildingImage(bool isDefaultSize = true);
	string getBuildingImagePath();
	string getBuildingImageId() const;
	double getAnchorX() const;
	double getAnchorY() const;
	double getPosX() const;
	double getPosY() const;
	string description() const;
	static const map<int, CityBuildingData*>* getSharedDictionary();
	static CityBuildingData* getCityBuildingDataById(int buildingId);
	static CityBuildingData* getCityBuildingDataById(const string& buildingId);
};
#endif
