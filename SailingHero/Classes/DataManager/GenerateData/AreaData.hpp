/*
This file (AreaData.hpp) is generated
*/
#ifndef AreaData_hpp
#define AreaData_hpp
#include <map>
#include "BaseData.h"

class AreaData;
class AreaData;
class AreaData;
class AreaData;
class AreaData;
class AreaData;

class AreaData: public BaseData
{
private:
	static map<int, AreaData*>* p_sharedDictionary;
	int p_areaId;
	string p_iconId;
	string p_leftId;
	string p_rightUpId;
	string p_rightId;
	string p_rightDownId;
	string p_upId;
	string p_downId;
	double p_x1;
	double p_y1;
	double p_x2;
	double p_y2;
public:
	string getId() const;
	int getAreaId() const;
	string getAreaName() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconPath();
	string getIconId() const;
	AreaData* getLeftData() const;
	string getLeftId() const;
	AreaData* getRightUpData() const;
	string getRightUpId() const;
	AreaData* getRightData() const;
	string getRightId() const;
	AreaData* getRightDownData() const;
	string getRightDownId() const;
	AreaData* getUpData() const;
	string getUpId() const;
	AreaData* getDownData() const;
	string getDownId() const;
	double getX1() const;
	double getY1() const;
	double getX2() const;
	double getY2() const;
	string description() const;
	static const map<int, AreaData*>* getSharedDictionary();
	static AreaData* getAreaDataById(int areaId);
	static AreaData* getAreaDataById(const string& areaId);
};
#endif
