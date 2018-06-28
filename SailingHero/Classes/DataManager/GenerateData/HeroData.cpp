/*
This file (HeroData.cpp) is generated at 2018-06-27 22:21:10
*/
#include "HeroData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;
string HeroData::getHeroId() const
{
	return p_heroId;
}

string HeroData::getHeroFirstName() const
{
	string localId = "hero_heroFirstName_" + p_heroId;
	return LocalizationHelper::getLocalization(localId);
}

string HeroData::getHeroLastName() const
{
	string localId = "hero_heroLastName_" + p_heroId;
	return LocalizationHelper::getLocalization(localId);
}

GenderData* HeroData::getGenderData() const
{
	return GenderData::getGenderDataById(p_genderId);
}

string HeroData::getGenderId() const
{
	return p_genderId;
}

int HeroData::getLevel() const
{
	return p_level;
}

int HeroData::getPhysicalStrength() const
{
	return p_physicalStrength;
}

int HeroData::getAgility() const
{
	return p_agility;
}

int HeroData::getCharm() const
{
	return p_charm;
}

int HeroData::getIntelligence() const
{
	return p_intelligence;
}

int HeroData::getMentalStrength() const
{
	return p_mentalStrength;
}

int HeroData::getLuck() const
{
	return p_luck;
}

int HeroData::getHealthPoint() const
{
	return p_healthPoint;
}

int HeroData::getCommandingAbility() const
{
	return p_commandingAbility;
}

int HeroData::getDrivingAbility() const
{
	return p_drivingAbility;
}

int HeroData::getMeasuringAbility() const
{
	return p_measuringAbility;
}

int HeroData::getAccountingAbility() const
{
	return p_accountingAbility;
}

int HeroData::getFencingAbility() const
{
	return p_fencingAbility;
}

int HeroData::getAimingAbility() const
{
	return p_aimingAbility;
}

int HeroData::getEloquence() const
{
	return p_eloquence;
}

int HeroData::getStrategyAbility() const
{
	return p_strategyAbility;
}

int HeroData::getObservingAbility() const
{
	return p_observingAbility;
}

string HeroData::description() const
{
	string desc = "heroData = {\n";
	desc += "\theroId : " + to_string(p_heroId) + "\n";
	desc += "\theroFirstName : " + getHeroFirstName() + "\n";
	desc += "\theroLastName : " + getHeroLastName() + "\n";
	desc += "\tgenderId : " + to_string(p_genderId) + "\n";
	desc += "\tlevel : " + to_string(p_level) + "\n";
	desc += "\tphysicalStrength : " + to_string(p_physicalStrength) + "\n";
	desc += "\tagility : " + to_string(p_agility) + "\n";
	desc += "\tcharm : " + to_string(p_charm) + "\n";
	desc += "\tintelligence : " + to_string(p_intelligence) + "\n";
	desc += "\tmentalStrength : " + to_string(p_mentalStrength) + "\n";
	desc += "\tluck : " + to_string(p_luck) + "\n";
	desc += "\thealthPoint : " + to_string(p_healthPoint) + "\n";
	desc += "\tcommandingAbility : " + to_string(p_commandingAbility) + "\n";
	desc += "\tdrivingAbility : " + to_string(p_drivingAbility) + "\n";
	desc += "\tmeasuringAbility : " + to_string(p_measuringAbility) + "\n";
	desc += "\taccountingAbility : " + to_string(p_accountingAbility) + "\n";
	desc += "\tfencingAbility : " + to_string(p_fencingAbility) + "\n";
	desc += "\taimingAbility : " + to_string(p_aimingAbility) + "\n";
	desc += "\teloquence : " + to_string(p_eloquence) + "\n";
	desc += "\tstrategyAbility : " + to_string(p_strategyAbility) + "\n";
	desc += "\tobservingAbility : " + to_string(p_observingAbility) + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, HeroData*>* HeroData::getSharedDictionary()
{
	static unordered_map<string, HeroData*>* sharedDictionary = nullptr;
	if (!sharedDictionary) {
		sharedDictionary = new unordered_map<string, HeroData*>();
		static string resPath = "res/base/data/hero.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				HeroData* heroData = new HeroData();
				heroData->p_heroId = buffer->getString();
				heroData->p_genderId = buffer->getString();
				heroData->p_level = buffer->getInt();
				heroData->p_physicalStrength = buffer->getInt();
				heroData->p_agility = buffer->getInt();
				heroData->p_charm = buffer->getInt();
				heroData->p_intelligence = buffer->getInt();
				heroData->p_mentalStrength = buffer->getInt();
				heroData->p_luck = buffer->getInt();
				heroData->p_healthPoint = buffer->getInt();
				heroData->p_commandingAbility = buffer->getInt();
				heroData->p_drivingAbility = buffer->getInt();
				heroData->p_measuringAbility = buffer->getInt();
				heroData->p_accountingAbility = buffer->getInt();
				heroData->p_fencingAbility = buffer->getInt();
				heroData->p_aimingAbility = buffer->getInt();
				heroData->p_eloquence = buffer->getInt();
				heroData->p_strategyAbility = buffer->getInt();
				heroData->p_observingAbility = buffer->getInt();
				sharedDictionary->insert(pair<string, HeroData*>(heroData->p_heroId, heroData));
			}
		}
	}
	return sharedDictionary;
}

HeroData* HeroData::getHeroDataById(const string& heroId)
{
	if (HeroData::getSharedDictionary()->count(heroId)) {
		return HeroData::getSharedDictionary()->at(heroId);
	}
	CCLOGERROR("invalid heroId %s", heroId.c_str());
	return nullptr;
}

bool HeroData::saveData(const string & path)
{
	return true;
}

bool HeroData::loadData(const string & path)
{
	return true;
}

