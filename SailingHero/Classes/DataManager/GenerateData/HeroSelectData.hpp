/*
This file (HeroSelectData.hpp) is generated
*/
#ifndef HeroSelectData_hpp
#define HeroSelectData_hpp
#include <map>
#include "BaseData.h"
#include "GuildData.hpp"

using namespace std;
class HeroSelectData: public BaseData
{
private:
	static map<string, HeroSelectData*>* p_sharedDictionary;
	string p_selectHeroId;
	string p_iconId;
	string p_smallIconId;
	string p_guildId;
public:
	string getId() const;
	string getSelectHeroId() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconId() const;
	cocos2d::Sprite* getSmallIcon(bool isDefaultSize = true);
	string getSmallIconId() const;
	GuildData* getGuildData() const;
	string getGuildId() const;
	string getHeroDescription() const;
	string description() const;
	static map<string, HeroSelectData*>* getSharedDictionary();
	static HeroSelectData* getHeroSelectDataById(const string& selectHeroId);
};
#endif
