/*
This file (HeroData.hpp) is generated
*/
#ifndef HeroData_hpp
#define HeroData_hpp
#include <map>
#include "BaseData.h"
#include "GenderData.hpp"


class HeroData: public BaseData
{
private:
	static map<int, HeroData*>* p_sharedDictionary;
	int p_heroId;
	string p_heroFirstName;
	string p_heroLastName;
	string p_photoId;
	string p_genderId;
	int p_birthMonth;
	int p_birthDay;
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
	string getId() const;
	int getHeroId() const;
	void setHeroFirstName(string heroFirstName);
	string getHeroFirstName() const;
	void setHeroLastName(string heroLastName);
	string getHeroLastName() const;
	cocos2d::Sprite* getPhoto(bool isDefaultSize = true);
	string getPhotoPath();
	string getPhotoId() const;
	GenderData* getGenderData() const;
	string getGenderId() const;
	void setGenderId(string gender);
	int getBirthMonth() const;
	void setBirthMonth(int birthMonth);
	int getBirthDay() const;
	void setBirthDay(int birthDay);
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
	static const map<int, HeroData*>* getSharedDictionary();
	static HeroData* getHeroDataById(int heroId);
	static HeroData* getHeroDataById(const string& heroId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
