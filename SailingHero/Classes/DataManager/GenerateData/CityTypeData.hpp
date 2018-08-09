/*
This file (CityTypeData.hpp) is generated
*/
#ifndef CityTypeData_hpp
#define CityTypeData_hpp
#include <map>
#include "BaseData.h"


class CityTypeData: public BaseData
{
private:
	static map<int, CityTypeData*>* p_sharedDictionary;
	int p_cityTypeId;
	string p_cityUpIconId;
	string p_cityDownIconId;
public:
	string getId() const;
	int getCityTypeId() const;
	string getCityTypeName() const;
	cocos2d::Sprite* getCityUpIcon(bool isDefaultSize = true);
	string getCityUpIconPath();
	string getCityUpIconId() const;
	cocos2d::Sprite* getCityDownIcon(bool isDefaultSize = true);
	string getCityDownIconPath();
	string getCityDownIconId() const;
	string description() const;
	static const map<int, CityTypeData*>* getSharedDictionary();
	static CityTypeData* getCityTypeDataById(int cityTypeId);
	static CityTypeData* getCityTypeDataById(const string& cityTypeId);
};
#endif
