/*
This file (HeroSelectData.hpp) is generated
*/
#ifndef HeroSelectData_hpp
#define HeroSelectData_hpp
#include <map>
#include "HeroData.hpp"

using namespace std;
class HeroSelectData
{
private:
	static map<string, HeroSelectData*>* p_sharedDictionary;
	string p_selectHeroId;
	string p_iconId;
	string p_heroId;
public:
	string getSelectHeroId() const;
	cocos2d::Sprite* getIcon() const;
	string getIconId() const;
	HeroData* getHeroData() const;
	string getHeroId() const;
	string getHeroDescription() const;
	string description() const;
	static map<string, HeroSelectData*>* getSharedDictionary();
	static HeroSelectData* getHeroSelectDataById(const string& selectHeroId);
};
#endif
