/*
This file (HeroData.hpp) is generated at 2018-06-27 22:21:10
*/
#ifndef HeroData_hpp
#define HeroData_hpp
#include <unordered_map>
#include "GenderData.hpp"

using namespace std;
class HeroData
{
private:
	string p_heroId;
	string p_genderId;
	int p_level;
	int p_physicalStrength;
	int p_agility;
	int p_charm;
	int p_intelligence;
	int p_mentalStrength;
	int p_luck;
	int p_healthPoint;
	int p_commandingAbility;
	int p_drivingAbility;
	int p_measuringAbility;
	int p_accountingAbility;
	int p_fencingAbility;
	int p_aimingAbility;
	int p_eloquence;
	int p_strategyAbility;
	int p_observingAbility;
public:
	string getHeroId() const;
	string getHeroFirstName() const;
	string getHeroLastName() const;
	GenderData* getGenderData() const;
	string getGenderId() const;
	int getLevel() const;
	int getPhysicalStrength() const;
	int getAgility() const;
	int getCharm() const;
	int getIntelligence() const;
	int getMentalStrength() const;
	int getLuck() const;
	int getHealthPoint() const;
	int getCommandingAbility() const;
	int getDrivingAbility() const;
	int getMeasuringAbility() const;
	int getAccountingAbility() const;
	int getFencingAbility() const;
	int getAimingAbility() const;
	int getEloquence() const;
	int getStrategyAbility() const;
	int getObservingAbility() const;
	string description() const;
	static unordered_map<string, HeroData*>* getSharedDictionary();
	static HeroData* getHeroDataById(const string& heroId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
};
#endif
