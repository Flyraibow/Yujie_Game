/*
This file (HeroSelectData.hpp) is generated
*/
#ifndef HeroSelectData_hpp
#define HeroSelectData_hpp
#include <map>
#include "BaseData.h"
#include "CityData.hpp"
#include "GuildData.hpp"


class HeroSelectData: public BaseData
{
private:
	static map<int, HeroSelectData*>* p_sharedDictionary;
	int p_selectHeroId;
	string p_iconId;
	string p_smallIconId;
	string p_startCityIdId;
	string p_guildId;
public:
	string getId() const;
	int getSelectHeroId() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconPath();
	string getIconId() const;
	cocos2d::Sprite* getSmallIcon(bool isDefaultSize = true);
	string getSmallIconPath();
	string getSmallIconId() const;
	CityData* getStartCityIdData() const;
	string getStartCityIdId() const;
	GuildData* getGuildData() const;
	string getGuildId() const;
	string getHeroDescription() const;
	string description() const;
	static const map<int, HeroSelectData*>* getSharedDictionary();
	static HeroSelectData* getHeroSelectDataById(int selectHeroId);
	static HeroSelectData* getHeroSelectDataById(const string& selectHeroId);
};
#endif
