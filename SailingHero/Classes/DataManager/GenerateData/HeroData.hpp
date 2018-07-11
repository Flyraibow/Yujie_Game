/*
This file (HeroData.hpp) is generated at 2018-07-11 14:19:57
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
	string p_heroFirstName;
	string p_heroLastName;
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
	void setGenderId(string genderId);
	int getLevel() const;
	void setLevel(int level);
	int getPhysicalStrength() const;
	void setPhysicalStrength(int physicalStrength);
	int getAgility() const;
	void setAgility(int agility);
	int getCharm() const;
	void setCharm(int charm);
	int getIntelligence() const;
	void setIntelligence(int intelligence);
	int getMentalStrength() const;
	void setMentalStrength(int mentalStrength);
	int getLuck() const;
	void setLuck(int luck);
	int getHealthPoint() const;
	void setHealthPoint(int healthPoint);
	int getCommandingAbility() const;
	void setCommandingAbility(int commandingAbility);
	int getDrivingAbility() const;
	void setDrivingAbility(int drivingAbility);
	int getMeasuringAbility() const;
	void setMeasuringAbility(int measuringAbility);
	int getAccountingAbility() const;
	void setAccountingAbility(int accountingAbility);
	int getFencingAbility() const;
	void setFencingAbility(int fencingAbility);
	int getAimingAbility() const;
	void setAimingAbility(int aimingAbility);
	int getEloquence() const;
	void setEloquence(int eloquence);
	int getStrategyAbility() const;
	void setStrategyAbility(int strategyAbility);
	int getObservingAbility() const;
	void setObservingAbility(int observingAbility);
	string description() const;
	static unordered_map<string, HeroData*>* getSharedDictionary();
	static HeroData* getHeroDataById(const string& heroId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
};
#endif
