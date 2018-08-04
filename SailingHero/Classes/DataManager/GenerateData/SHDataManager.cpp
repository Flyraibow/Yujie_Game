/*
This file (SHDataManager.cpp) is generated
*/
#include "SHDataManager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cocos2d.h"
#include "GuildData.hpp"
#include "ShipTeamData.hpp"
#include "CityGoodsData.hpp"
#include "CityData.hpp"
#include "GameData.hpp"
#include "HeroData.hpp"




GoodsCategoryData* SHDataManager::getGoodsCategoryDataById(int categoryId)
{
	if (GoodsCategoryData::getSharedDictionary()->count(categoryId)) {
		return GoodsCategoryData::getSharedDictionary()->at(categoryId);
	}
	return nullptr;
}

GoodsCategoryData* SHDataManager::getGoodsCategoryDataById(const string& categoryId)
{
	if (categoryId.length() == 0) return nullptr;
	return GoodsCategoryData::getGoodsCategoryDataById(atoi(categoryId.c_str()));
}

GuildData* SHDataManager::getGuildDataById(int guildId)
{
	if (GuildData::getSharedDictionary()->count(guildId)) {
		return GuildData::getSharedDictionary()->at(guildId);
	}
	return nullptr;
}

GuildData* SHDataManager::getGuildDataById(const string& guildId)
{
	if (guildId.length() == 0) return nullptr;
	return GuildData::getGuildDataById(atoi(guildId.c_str()));
}

GenderData* SHDataManager::getGenderDataById(int genderId)
{
	if (GenderData::getSharedDictionary()->count(genderId)) {
		return GenderData::getSharedDictionary()->at(genderId);
	}
	return nullptr;
}

GenderData* SHDataManager::getGenderDataById(const string& genderId)
{
	if (genderId.length() == 0) return nullptr;
	return GenderData::getGenderDataById(atoi(genderId.c_str()));
}

CultureData* SHDataManager::getCultureDataById(int cutureId)
{
	if (CultureData::getSharedDictionary()->count(cutureId)) {
		return CultureData::getSharedDictionary()->at(cutureId);
	}
	return nullptr;
}

CultureData* SHDataManager::getCultureDataById(const string& cutureId)
{
	if (cutureId.length() == 0) return nullptr;
	return CultureData::getCultureDataById(atoi(cutureId.c_str()));
}

AbilityData* SHDataManager::getAbilityDataById(int abilityId)
{
	if (AbilityData::getSharedDictionary()->count(abilityId)) {
		return AbilityData::getSharedDictionary()->at(abilityId);
	}
	return nullptr;
}

AbilityData* SHDataManager::getAbilityDataById(const string& abilityId)
{
	if (abilityId.length() == 0) return nullptr;
	return AbilityData::getAbilityDataById(atoi(abilityId.c_str()));
}

CityTypeData* SHDataManager::getCityTypeDataById(int cityTypeId)
{
	if (CityTypeData::getSharedDictionary()->count(cityTypeId)) {
		return CityTypeData::getSharedDictionary()->at(cityTypeId);
	}
	return nullptr;
}

CityTypeData* SHDataManager::getCityTypeDataById(const string& cityTypeId)
{
	if (cityTypeId.length() == 0) return nullptr;
	return CityTypeData::getCityTypeDataById(atoi(cityTypeId.c_str()));
}

SystemButtonData* SHDataManager::getSystemButtonDataById(int buttonId)
{
	if (SystemButtonData::getSharedDictionary()->count(buttonId)) {
		return SystemButtonData::getSharedDictionary()->at(buttonId);
	}
	return nullptr;
}

SystemButtonData* SHDataManager::getSystemButtonDataById(const string& buttonId)
{
	if (buttonId.length() == 0) return nullptr;
	return SystemButtonData::getSystemButtonDataById(atoi(buttonId.c_str()));
}

ShipTeamData* SHDataManager::getShipTeamDataById(int shipTeamId)
{
	if (ShipTeamData::getSharedDictionary()->count(shipTeamId)) {
		return ShipTeamData::getSharedDictionary()->at(shipTeamId);
	}
	return nullptr;
}

ShipTeamData* SHDataManager::getShipTeamDataById(const string& shipTeamId)
{
	if (shipTeamId.length() == 0) return nullptr;
	return ShipTeamData::getShipTeamDataById(atoi(shipTeamId.c_str()));
}

DialogData* SHDataManager::getDialogDataById(const string& dialogId)
{
	if (DialogData::getSharedDictionary()->count(dialogId)) {
		return DialogData::getSharedDictionary()->at(dialogId);
	}
	return nullptr;
}

ItemData* SHDataManager::getItemDataById(int itemId)
{
	if (ItemData::getSharedDictionary()->count(itemId)) {
		return ItemData::getSharedDictionary()->at(itemId);
	}
	return nullptr;
}

ItemData* SHDataManager::getItemDataById(const string& itemId)
{
	if (itemId.length() == 0) return nullptr;
	return ItemData::getItemDataById(atoi(itemId.c_str()));
}

ShipSizeData* SHDataManager::getShipSizeDataById(int shipSizeId)
{
	if (ShipSizeData::getSharedDictionary()->count(shipSizeId)) {
		return ShipSizeData::getSharedDictionary()->at(shipSizeId);
	}
	return nullptr;
}

ShipSizeData* SHDataManager::getShipSizeDataById(const string& shipSizeId)
{
	if (shipSizeId.length() == 0) return nullptr;
	return ShipSizeData::getShipSizeDataById(atoi(shipSizeId.c_str()));
}

CityGoodsData* SHDataManager::getCityGoodsDataById(int cityGoodsId)
{
	if (CityGoodsData::getSharedDictionary()->count(cityGoodsId)) {
		return CityGoodsData::getSharedDictionary()->at(cityGoodsId);
	}
	return nullptr;
}

CityGoodsData* SHDataManager::getCityGoodsDataById(const string& cityGoodsId)
{
	if (cityGoodsId.length() == 0) return nullptr;
	return CityGoodsData::getCityGoodsDataById(atoi(cityGoodsId.c_str()));
}

ShipStyleData* SHDataManager::getShipStyleDataById(int shipStyleId)
{
	if (ShipStyleData::getSharedDictionary()->count(shipStyleId)) {
		return ShipStyleData::getSharedDictionary()->at(shipStyleId);
	}
	return nullptr;
}

ShipStyleData* SHDataManager::getShipStyleDataById(const string& shipStyleId)
{
	if (shipStyleId.length() == 0) return nullptr;
	return ShipStyleData::getShipStyleDataById(atoi(shipStyleId.c_str()));
}

CannonData* SHDataManager::getCannonDataById(int cannonId)
{
	if (CannonData::getSharedDictionary()->count(cannonId)) {
		return CannonData::getSharedDictionary()->at(cannonId);
	}
	return nullptr;
}

CannonData* SHDataManager::getCannonDataById(const string& cannonId)
{
	if (cannonId.length() == 0) return nullptr;
	return CannonData::getCannonDataById(atoi(cannonId.c_str()));
}

GoodsData* SHDataManager::getGoodsDataById(int goodsId)
{
	if (GoodsData::getSharedDictionary()->count(goodsId)) {
		return GoodsData::getSharedDictionary()->at(goodsId);
	}
	return nullptr;
}

GoodsData* SHDataManager::getGoodsDataById(const string& goodsId)
{
	if (goodsId.length() == 0) return nullptr;
	return GoodsData::getGoodsDataById(atoi(goodsId.c_str()));
}

ItemCategoryData* SHDataManager::getItemCategoryDataById(int itemCategoryId)
{
	if (ItemCategoryData::getSharedDictionary()->count(itemCategoryId)) {
		return ItemCategoryData::getSharedDictionary()->at(itemCategoryId);
	}
	return nullptr;
}

ItemCategoryData* SHDataManager::getItemCategoryDataById(const string& itemCategoryId)
{
	if (itemCategoryId.length() == 0) return nullptr;
	return ItemCategoryData::getItemCategoryDataById(atoi(itemCategoryId.c_str()));
}

CityData* SHDataManager::getCityDataById(int cityId)
{
	if (CityData::getSharedDictionary()->count(cityId)) {
		return CityData::getSharedDictionary()->at(cityId);
	}
	return nullptr;
}

CityData* SHDataManager::getCityDataById(const string& cityId)
{
	if (cityId.length() == 0) return nullptr;
	return CityData::getCityDataById(atoi(cityId.c_str()));
}

TownPhotoData* SHDataManager::getTownPhotoDataById(const string& townPhotoId)
{
	if (TownPhotoData::getSharedDictionary()->count(townPhotoId)) {
		return TownPhotoData::getSharedDictionary()->at(townPhotoId);
	}
	return nullptr;
}

ZodiacData* SHDataManager::getZodiacDataById(int zodiacId)
{
	if (ZodiacData::getSharedDictionary()->count(zodiacId)) {
		return ZodiacData::getSharedDictionary()->at(zodiacId);
	}
	return nullptr;
}

ZodiacData* SHDataManager::getZodiacDataById(const string& zodiacId)
{
	if (zodiacId.length() == 0) return nullptr;
	return ZodiacData::getZodiacDataById(atoi(zodiacId.c_str()));
}

CityBuildingData* SHDataManager::getCityBuildingDataById(int buildingId)
{
	if (CityBuildingData::getSharedDictionary()->count(buildingId)) {
		return CityBuildingData::getSharedDictionary()->at(buildingId);
	}
	return nullptr;
}

CityBuildingData* SHDataManager::getCityBuildingDataById(const string& buildingId)
{
	if (buildingId.length() == 0) return nullptr;
	return CityBuildingData::getCityBuildingDataById(atoi(buildingId.c_str()));
}

HeroSelectData* SHDataManager::getHeroSelectDataById(int selectHeroId)
{
	if (HeroSelectData::getSharedDictionary()->count(selectHeroId)) {
		return HeroSelectData::getSharedDictionary()->at(selectHeroId);
	}
	return nullptr;
}

HeroSelectData* SHDataManager::getHeroSelectDataById(const string& selectHeroId)
{
	if (selectHeroId.length() == 0) return nullptr;
	return HeroSelectData::getHeroSelectDataById(atoi(selectHeroId.c_str()));
}

CategoryUpdateData* SHDataManager::getCategoryUpdateDataById(int categoryUpdateId)
{
	if (CategoryUpdateData::getSharedDictionary()->count(categoryUpdateId)) {
		return CategoryUpdateData::getSharedDictionary()->at(categoryUpdateId);
	}
	return nullptr;
}

CategoryUpdateData* SHDataManager::getCategoryUpdateDataById(const string& categoryUpdateId)
{
	if (categoryUpdateId.length() == 0) return nullptr;
	return CategoryUpdateData::getCategoryUpdateDataById(atoi(categoryUpdateId.c_str()));
}

ShipData* SHDataManager::getShipDataById(int cannonId)
{
	if (ShipData::getSharedDictionary()->count(cannonId)) {
		return ShipData::getSharedDictionary()->at(cannonId);
	}
	return nullptr;
}

ShipData* SHDataManager::getShipDataById(const string& cannonId)
{
	if (cannonId.length() == 0) return nullptr;
	return ShipData::getShipDataById(atoi(cannonId.c_str()));
}

GameData* SHDataManager::getGameData()
{
	return GameData::getSharedInstance();
}

HeroData* SHDataManager::getHeroDataById(int heroId)
{
	if (HeroData::getSharedDictionary()->count(heroId)) {
		return HeroData::getSharedDictionary()->at(heroId);
	}
	return nullptr;
}

HeroData* SHDataManager::getHeroDataById(const string& heroId)
{
	if (heroId.length() == 0) return nullptr;
	return HeroData::getHeroDataById(atoi(heroId.c_str()));
}

CityStatusData* SHDataManager::getCityStatusDataById(int cityStatusId)
{
	if (CityStatusData::getSharedDictionary()->count(cityStatusId)) {
		return CityStatusData::getSharedDictionary()->at(cityStatusId);
	}
	return nullptr;
}

CityStatusData* SHDataManager::getCityStatusDataById(const string& cityStatusId)
{
	if (cityStatusId.length() == 0) return nullptr;
	return CityStatusData::getCityStatusDataById(atoi(cityStatusId.c_str()));
}

bool SHDataManager::saveData(int index)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + to_string(index);
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		mkdir(path.c_str(), 0700);
	}
	if (!GuildData::saveData(path)) {
		CCLOG("Failed to save GuildData, %s", path.c_str());
		return false;
	}
	if (!ShipTeamData::saveData(path)) {
		CCLOG("Failed to save ShipTeamData, %s", path.c_str());
		return false;
	}
	if (!CityGoodsData::saveData(path)) {
		CCLOG("Failed to save CityGoodsData, %s", path.c_str());
		return false;
	}
	if (!CityData::saveData(path)) {
		CCLOG("Failed to save CityData, %s", path.c_str());
		return false;
	}
	if (!GameData::saveData(path)) {
		CCLOG("Failed to save GameData, %s", path.c_str());
		return false;
	}
	if (!HeroData::saveData(path)) {
		CCLOG("Failed to save HeroData, %s", path.c_str());
		return false;
	}
	return true;
}

bool SHDataManager::loadData(int index)
{
	string path = cocos2d::FileUtils::getInstance()->getWritablePath() + "/" + to_string(index);
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
		CCLOG("Failed to load data, there is no folder %s", path.c_str());
		return false;
	}
	if (!GuildData::loadData(path)) {
		CCLOG("Failed to load GuildData, %s", path.c_str());
		return false;
	}
	if (!ShipTeamData::loadData(path)) {
		CCLOG("Failed to load ShipTeamData, %s", path.c_str());
		return false;
	}
	if (!CityGoodsData::loadData(path)) {
		CCLOG("Failed to load CityGoodsData, %s", path.c_str());
		return false;
	}
	if (!CityData::loadData(path)) {
		CCLOG("Failed to load CityData, %s", path.c_str());
		return false;
	}
	if (!GameData::loadData(path)) {
		CCLOG("Failed to load GameData, %s", path.c_str());
		return false;
	}
	if (!HeroData::loadData(path)) {
		CCLOG("Failed to load HeroData, %s", path.c_str());
		return false;
	}
	return true;
}

bool SHDataManager::clearData()
{
	GuildData::clearData();
	ShipTeamData::clearData();
	CityGoodsData::clearData();
	CityData::clearData();
	GameData::clearData();
	HeroData::clearData();
	return true;
}

