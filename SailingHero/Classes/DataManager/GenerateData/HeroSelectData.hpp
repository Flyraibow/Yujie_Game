/*
This file (HeroSelectData.hpp) is generated
*/
#ifndef HeroSelectData_hpp
#define HeroSelectData_hpp
#include <map>
#include "GuildData.hpp"

using namespace std;
class HeroSelectData
{
private:
	static map<string, HeroSelectData*>* p_sharedDictionary;
	string p_selectHeroId;
	string p_iconId;
	string p_smallIconId;
	string p_heroId;
public:
	string getSelectHeroId() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconId() const;
	cocos2d::Sprite* getSmallIcon(bool isDefaultSize = true);
	string getSmallIconId() const;
	GuildData* getGuildData() const;
	string getHeroId() const;
	string getHeroDescription() const;
	string description() const;
	static map<string, HeroSelectData*>* getSharedDictionary();
	static HeroSelectData* getHeroSelectDataById(const string& selectHeroId);
};
#endif
