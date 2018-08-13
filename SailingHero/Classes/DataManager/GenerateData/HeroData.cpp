/*
This file (HeroData.cpp) is generated
*/
#include "HeroData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, HeroData*>* HeroData::p_sharedDictionary = nullptr;

string HeroData::getId() const
{
	return to_string(p_heroId);
}

int HeroData::getHeroId() const
{
	return p_heroId;
}

void HeroData::setHeroFirstName(string heroFirstName)
{
	p_heroFirstName = heroFirstName;
}

string HeroData::getHeroFirstName() const
{
	if (p_heroFirstName.length() > 0) {
		return p_heroFirstName;
	}
	string localId = "hero_heroFirstName_" + to_string(p_heroId);
	return LocalizationHelper::getLocalization(localId);
}

void HeroData::setHeroLastName(string heroLastName)
{
	p_heroLastName = heroLastName;
}

string HeroData::getHeroLastName() const
{
	if (p_heroLastName.length() > 0) {
		return p_heroLastName;
	}
	string localId = "hero_heroLastName_" + to_string(p_heroId);
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* HeroData::getPhoto(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/bustup/";
	string path = s_basePath + p_photoId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string HeroData::getPhotoPath()
{
	static const string s_basePath = "res/base/icon/bustup/";
	return s_basePath + p_photoId;
}

string HeroData::getPhotoId() const
{
	return p_photoId;
}

GenderData* HeroData::getGenderData() const
{
	return GenderData::getGenderDataById(p_genderId);
}

string HeroData::getGenderId() const
{
	return p_genderId;
}

void HeroData::setGenderId(string gender)
{
	p_genderId = gender;
}

int HeroData::getBirthMonth() const
{
	return p_birthMonth;
}

void HeroData::setBirthMonth(int birthMonth)
{
	p_birthMonth = birthMonth;
}

int HeroData::getBirthDay() const
{
	return p_birthDay;
}

void HeroData::setBirthDay(int birthDay)
{
	p_birthDay = birthDay;
}

int HeroData::getLevel() const
{
	return p_level;
}

void HeroData::setLevel(int level)
{
	p_level = level;
}

int HeroData::getPhysicalStrength() const
{
	return p_physicalStrength;
}

void HeroData::setPhysicalStrength(int physicalStrength)
{
	p_physicalStrength = physicalStrength;
}

int HeroData::getAgility() const
{
	return p_agility;
}

void HeroData::setAgility(int agility)
{
	p_agility = agility;
}

int HeroData::getCharm() const
{
	return p_charm;
}

void HeroData::setCharm(int charm)
{
	p_charm = charm;
}

int HeroData::getIntelligence() const
{
	return p_intelligence;
}

void HeroData::setIntelligence(int intelligence)
{
	p_intelligence = intelligence;
}

int HeroData::getMentalStrength() const
{
	return p_mentalStrength;
}

void HeroData::setMentalStrength(int mentalStrength)
{
	p_mentalStrength = mentalStrength;
}

int HeroData::getLuck() const
{
	return p_luck;
}

void HeroData::setLuck(int luck)
{
	p_luck = luck;
}

int HeroData::getHealthPoint() const
{
	return p_healthPoint;
}

void HeroData::setHealthPoint(int healthPoint)
{
	p_healthPoint = healthPoint;
}

int HeroData::getCommandingAbility() const
{
	return p_commandingAbility;
}

void HeroData::setCommandingAbility(int commandingAbility)
{
	p_commandingAbility = commandingAbility;
}

int HeroData::getDrivingAbility() const
{
	return p_drivingAbility;
}

void HeroData::setDrivingAbility(int drivingAbility)
{
	p_drivingAbility = drivingAbility;
}

int HeroData::getMeasuringAbility() const
{
	return p_measuringAbility;
}

void HeroData::setMeasuringAbility(int measuringAbility)
{
	p_measuringAbility = measuringAbility;
}

int HeroData::getAccountingAbility() const
{
	return p_accountingAbility;
}

void HeroData::setAccountingAbility(int accountingAbility)
{
	p_accountingAbility = accountingAbility;
}

int HeroData::getFencingAbility() const
{
	return p_fencingAbility;
}

void HeroData::setFencingAbility(int fencingAbility)
{
	p_fencingAbility = fencingAbility;
}

int HeroData::getAimingAbility() const
{
	return p_aimingAbility;
}

void HeroData::setAimingAbility(int aimingAbility)
{
	p_aimingAbility = aimingAbility;
}

int HeroData::getEloquence() const
{
	return p_eloquence;
}

void HeroData::setEloquence(int eloquence)
{
	p_eloquence = eloquence;
}

int HeroData::getStrategyAbility() const
{
	return p_strategyAbility;
}

void HeroData::setStrategyAbility(int strategyAbility)
{
	p_strategyAbility = strategyAbility;
}

int HeroData::getObservingAbility() const
{
	return p_observingAbility;
}

void HeroData::setObservingAbility(int observingAbility)
{
	p_observingAbility = observingAbility;
}

string HeroData::description() const
{
	string desc = "heroData = {\n";
	desc += "\theroId : " + to_string(p_heroId) + "\n";
	desc += "\theroFirstName : " + getHeroFirstName() + "\n";
	desc += "\theroLastName : " + getHeroLastName() + "\n";
	desc += "\tphotoId : " + to_string(p_photoId) + "\n";
	desc += "\tgender : " + to_string(p_genderId) + "\n";
	desc += "\tbirthMonth : " + to_string(p_birthMonth) + "\n";
	desc += "\tbirthDay : " + to_string(p_birthDay) + "\n";
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

const map<int, HeroData*>* HeroData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, HeroData*>();
		static string resPath = "res/base/data/hero.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				HeroData* heroData = new HeroData();
				heroData->p_heroId = buffer->getInt();
				heroData->p_photoId = buffer->getString();
				heroData->p_genderId = buffer->getString();
				heroData->p_birthMonth = buffer->getInt();
				heroData->p_birthDay = buffer->getInt();
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
				p_sharedDictionary->insert(pair<int, HeroData*>(heroData->p_heroId, heroData));
			}
		}
	}
	return p_sharedDictionary;
}

HeroData* HeroData::getHeroDataById(int heroId)
{
	if (HeroData::getSharedDictionary()->count(heroId)) {
		return HeroData::getSharedDictionary()->at(heroId);
	}
	return nullptr;
}

HeroData* HeroData::getHeroDataById(const string& heroId)
{
	if (heroId.length() == 0) return nullptr;
	return HeroData::getHeroDataById(atoi(heroId.c_str()));
}

bool HeroData::saveData(const string & path)
{
	auto filePath = path + "/HeroData.dat";
	auto dict = HeroData::getSharedDictionary();
	auto buffer = std::make_unique<bb::ByteBuffer>();
	buffer->putLong(dict->size());
	buffer->putInt(22);
	for (auto iter = dict->begin(); iter != dict->end(); iter++) {
		auto dataId = iter->first;
		auto data = iter->second;
		buffer->putInt(dataId);
		buffer->putString("p_heroFirstName");
		buffer->putString(to_string(data->p_heroFirstName));
		buffer->putString("p_heroLastName");
		buffer->putString(to_string(data->p_heroLastName));
		buffer->putString("p_genderId");
		buffer->putString(to_string(data->p_genderId));
		buffer->putString("p_birthMonth");
		buffer->putString(to_string(data->p_birthMonth));
		buffer->putString("p_birthDay");
		buffer->putString(to_string(data->p_birthDay));
		buffer->putString("p_level");
		buffer->putString(to_string(data->p_level));
		buffer->putString("p_physicalStrength");
		buffer->putString(to_string(data->p_physicalStrength));
		buffer->putString("p_agility");
		buffer->putString(to_string(data->p_agility));
		buffer->putString("p_charm");
		buffer->putString(to_string(data->p_charm));
		buffer->putString("p_intelligence");
		buffer->putString(to_string(data->p_intelligence));
		buffer->putString("p_mentalStrength");
		buffer->putString(to_string(data->p_mentalStrength));
		buffer->putString("p_luck");
		buffer->putString(to_string(data->p_luck));
		buffer->putString("p_healthPoint");
		buffer->putString(to_string(data->p_healthPoint));
		buffer->putString("p_commandingAbility");
		buffer->putString(to_string(data->p_commandingAbility));
		buffer->putString("p_drivingAbility");
		buffer->putString(to_string(data->p_drivingAbility));
		buffer->putString("p_measuringAbility");
		buffer->putString(to_string(data->p_measuringAbility));
		buffer->putString("p_accountingAbility");
		buffer->putString(to_string(data->p_accountingAbility));
		buffer->putString("p_fencingAbility");
		buffer->putString(to_string(data->p_fencingAbility));
		buffer->putString("p_aimingAbility");
		buffer->putString(to_string(data->p_aimingAbility));
		buffer->putString("p_eloquence");
		buffer->putString(to_string(data->p_eloquence));
		buffer->putString("p_strategyAbility");
		buffer->putString(to_string(data->p_strategyAbility));
		buffer->putString("p_observingAbility");
		buffer->putString(to_string(data->p_observingAbility));
	}
	buffer->writeToFile(filePath);
	return true;
}

bool HeroData::loadData(const string & path)
{
	auto filePath = path + "/HeroData.dat";
	auto dict = HeroData::getSharedDictionary();
	auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
	if (!fileData.isNull()) {
		auto bytes = fileData.getBytes();
		auto buffer = std::make_unique<bb::ByteBuffer>(bytes, fileData.getSize());
		auto size = buffer->getLong();
		auto dataSize = buffer->getInt();
		for (int i = 0; i < size; ++i) {
			auto dataId = buffer->getInt();
			HeroData *data = nullptr;
			if (dict->count(dataId)) {
				data = dict->at(dataId);
			}
			for (int j = 0; j < dataSize; ++j) {
				string key = buffer->getString();
				string value = buffer->getString();
				if (data != nullptr) {
					if (key == "p_heroFirstName") {
						data->p_heroFirstName = value;
					} else if (key == "p_heroLastName") {
						data->p_heroLastName = value;
					} else if (key == "p_genderId") {
						data->p_genderId = value;
					} else if (key == "p_birthMonth") {
						data->p_birthMonth = atoi(value.c_str());
					} else if (key == "p_birthDay") {
						data->p_birthDay = atoi(value.c_str());
					} else if (key == "p_level") {
						data->p_level = atoi(value.c_str());
					} else if (key == "p_physicalStrength") {
						data->p_physicalStrength = atoi(value.c_str());
					} else if (key == "p_agility") {
						data->p_agility = atoi(value.c_str());
					} else if (key == "p_charm") {
						data->p_charm = atoi(value.c_str());
					} else if (key == "p_intelligence") {
						data->p_intelligence = atoi(value.c_str());
					} else if (key == "p_mentalStrength") {
						data->p_mentalStrength = atoi(value.c_str());
					} else if (key == "p_luck") {
						data->p_luck = atoi(value.c_str());
					} else if (key == "p_healthPoint") {
						data->p_healthPoint = atoi(value.c_str());
					} else if (key == "p_commandingAbility") {
						data->p_commandingAbility = atoi(value.c_str());
					} else if (key == "p_drivingAbility") {
						data->p_drivingAbility = atoi(value.c_str());
					} else if (key == "p_measuringAbility") {
						data->p_measuringAbility = atoi(value.c_str());
					} else if (key == "p_accountingAbility") {
						data->p_accountingAbility = atoi(value.c_str());
					} else if (key == "p_fencingAbility") {
						data->p_fencingAbility = atoi(value.c_str());
					} else if (key == "p_aimingAbility") {
						data->p_aimingAbility = atoi(value.c_str());
					} else if (key == "p_eloquence") {
						data->p_eloquence = atoi(value.c_str());
					} else if (key == "p_strategyAbility") {
						data->p_strategyAbility = atoi(value.c_str());
					} else if (key == "p_observingAbility") {
						data->p_observingAbility = atoi(value.c_str());
					}
				}
			}
		}
	}
	return true;
}

bool HeroData::clearData()
{
	if (p_sharedDictionary != nullptr) {
		for (auto iter = p_sharedDictionary->begin(); iter != p_sharedDictionary->end(); ++iter) {
			auto data = iter->second;
			delete data;
		}
		delete p_sharedDictionary;
		p_sharedDictionary = nullptr;
	}
	return true;
}

void HeroData::setFieldValue(const string & fieldName, const string & value)
{
	if (fieldName == "heroFirstName") {
		this->setHeroFirstName(value);
	} else if (fieldName == "heroLastName") {
		this->setHeroLastName(value);
	} else if (fieldName == "gender") {
		this->setGenderId(value);
	} else if (fieldName == "birthMonth") {
		this->setBirthMonth(atoi(value.c_str()));
	} else if (fieldName == "birthDay") {
		this->setBirthDay(atoi(value.c_str()));
	} else if (fieldName == "level") {
		this->setLevel(atoi(value.c_str()));
	} else if (fieldName == "physicalStrength") {
		this->setPhysicalStrength(atoi(value.c_str()));
	} else if (fieldName == "agility") {
		this->setAgility(atoi(value.c_str()));
	} else if (fieldName == "charm") {
		this->setCharm(atoi(value.c_str()));
	} else if (fieldName == "intelligence") {
		this->setIntelligence(atoi(value.c_str()));
	} else if (fieldName == "mentalStrength") {
		this->setMentalStrength(atoi(value.c_str()));
	} else if (fieldName == "luck") {
		this->setLuck(atoi(value.c_str()));
	} else if (fieldName == "healthPoint") {
		this->setHealthPoint(atoi(value.c_str()));
	} else if (fieldName == "commandingAbility") {
		this->setCommandingAbility(atoi(value.c_str()));
	} else if (fieldName == "drivingAbility") {
		this->setDrivingAbility(atoi(value.c_str()));
	} else if (fieldName == "measuringAbility") {
		this->setMeasuringAbility(atoi(value.c_str()));
	} else if (fieldName == "accountingAbility") {
		this->setAccountingAbility(atoi(value.c_str()));
	} else if (fieldName == "fencingAbility") {
		this->setFencingAbility(atoi(value.c_str()));
	} else if (fieldName == "aimingAbility") {
		this->setAimingAbility(atoi(value.c_str()));
	} else if (fieldName == "eloquence") {
		this->setEloquence(atoi(value.c_str()));
	} else if (fieldName == "strategyAbility") {
		this->setStrategyAbility(atoi(value.c_str()));
	} else if (fieldName == "observingAbility") {
		this->setObservingAbility(atoi(value.c_str()));
	}
}

string HeroData::getFieldValue(const string & fieldName)
{
	if (fieldName == "heroId") {
		return to_string(this->getHeroId());
	} else if (fieldName == "heroFirstName") {
		return to_string(this->getHeroFirstName());
	} else if (fieldName == "heroLastName") {
		return to_string(this->getHeroLastName());
	} else if (fieldName == "photoId") {
		return to_string(this->getPhotoId());
	} else if (fieldName == "gender") {
		return to_string(this->getGenderId());
	} else if (fieldName == "birthMonth") {
		return to_string(this->getBirthMonth());
	} else if (fieldName == "birthDay") {
		return to_string(this->getBirthDay());
	} else if (fieldName == "level") {
		return to_string(this->getLevel());
	} else if (fieldName == "physicalStrength") {
		return to_string(this->getPhysicalStrength());
	} else if (fieldName == "agility") {
		return to_string(this->getAgility());
	} else if (fieldName == "charm") {
		return to_string(this->getCharm());
	} else if (fieldName == "intelligence") {
		return to_string(this->getIntelligence());
	} else if (fieldName == "mentalStrength") {
		return to_string(this->getMentalStrength());
	} else if (fieldName == "luck") {
		return to_string(this->getLuck());
	} else if (fieldName == "healthPoint") {
		return to_string(this->getHealthPoint());
	} else if (fieldName == "commandingAbility") {
		return to_string(this->getCommandingAbility());
	} else if (fieldName == "drivingAbility") {
		return to_string(this->getDrivingAbility());
	} else if (fieldName == "measuringAbility") {
		return to_string(this->getMeasuringAbility());
	} else if (fieldName == "accountingAbility") {
		return to_string(this->getAccountingAbility());
	} else if (fieldName == "fencingAbility") {
		return to_string(this->getFencingAbility());
	} else if (fieldName == "aimingAbility") {
		return to_string(this->getAimingAbility());
	} else if (fieldName == "eloquence") {
		return to_string(this->getEloquence());
	} else if (fieldName == "strategyAbility") {
		return to_string(this->getStrategyAbility());
	} else if (fieldName == "observingAbility") {
		return to_string(this->getObservingAbility());
	}
	CCLOGWARN("Couldn't recognize %s in HeroData", fieldName.c_str());
	return "";
}

