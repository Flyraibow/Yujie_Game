/*
This file (SHDataManager.hpp) is generated
*/
#ifndef SHDataManager_hpp
#define SHDataManager_hpp
#include "GoodsCategoryData.hpp"
#include "GuildData.hpp"
#include "GenderData.hpp"
#include "CultureData.hpp"
#include "AbilityData.hpp"
#include "CityTypeData.hpp"
#include "SystemButtonData.hpp"
#include "ShipTeamData.hpp"
#include "DialogData.hpp"
#include "ItemData.hpp"
#include "ShipSizeData.hpp"
#include "CityGoodsData.hpp"
#include "ShipStyleData.hpp"
#include "CannonData.hpp"
#include "GoodsData.hpp"
#include "ItemCategoryData.hpp"
#include "CityData.hpp"
#include "TownPhotoData.hpp"
#include "ZodiacData.hpp"
#include "CityBuildingData.hpp"
#include "HeroSelectData.hpp"
#include "CategoryUpdateData.hpp"
#include "ShipData.hpp"
#include "GameData.hpp"
#include "HeroData.hpp"
#include "CityStatusData.hpp"


class SHDataManager
{
private:
public:
	static GoodsCategoryData* getGoodsCategoryDataById(int categoryId);
	static GoodsCategoryData* getGoodsCategoryDataById(const string& categoryId);
	static GuildData* getGuildDataById(int guildId);
	static GuildData* getGuildDataById(const string& guildId);
	static GenderData* getGenderDataById(int genderId);
	static GenderData* getGenderDataById(const string& genderId);
	static CultureData* getCultureDataById(int cutureId);
	static CultureData* getCultureDataById(const string& cutureId);
	static AbilityData* getAbilityDataById(int abilityId);
	static AbilityData* getAbilityDataById(const string& abilityId);
	static CityTypeData* getCityTypeDataById(int cityTypeId);
	static CityTypeData* getCityTypeDataById(const string& cityTypeId);
	static SystemButtonData* getSystemButtonDataById(int buttonId);
	static SystemButtonData* getSystemButtonDataById(const string& buttonId);
	static ShipTeamData* getShipTeamDataById(int shipTeamId);
	static ShipTeamData* getShipTeamDataById(const string& shipTeamId);
	static DialogData* getDialogDataById(const string& dialogId);
	static ItemData* getItemDataById(int itemId);
	static ItemData* getItemDataById(const string& itemId);
	static ShipSizeData* getShipSizeDataById(int shipSizeId);
	static ShipSizeData* getShipSizeDataById(const string& shipSizeId);
	static CityGoodsData* getCityGoodsDataById(int cityGoodsId);
	static CityGoodsData* getCityGoodsDataById(const string& cityGoodsId);
	static ShipStyleData* getShipStyleDataById(int shipStyleId);
	static ShipStyleData* getShipStyleDataById(const string& shipStyleId);
	static CannonData* getCannonDataById(int cannonId);
	static CannonData* getCannonDataById(const string& cannonId);
	static GoodsData* getGoodsDataById(int goodsId);
	static GoodsData* getGoodsDataById(const string& goodsId);
	static ItemCategoryData* getItemCategoryDataById(int itemCategoryId);
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
	static CityData* getCityDataById(int cityId);
	static CityData* getCityDataById(const string& cityId);
	static TownPhotoData* getTownPhotoDataById(const string& townPhotoId);
	static ZodiacData* getZodiacDataById(int zodiacId);
	static ZodiacData* getZodiacDataById(const string& zodiacId);
	static CityBuildingData* getCityBuildingDataById(int buildingId);
	static CityBuildingData* getCityBuildingDataById(const string& buildingId);
	static HeroSelectData* getHeroSelectDataById(int selectHeroId);
	static HeroSelectData* getHeroSelectDataById(const string& selectHeroId);
	static CategoryUpdateData* getCategoryUpdateDataById(int categoryUpdateId);
	static CategoryUpdateData* getCategoryUpdateDataById(const string& categoryUpdateId);
	static ShipData* getShipDataById(int cannonId);
	static ShipData* getShipDataById(const string& cannonId);
	static GameData* getGameData();
	static HeroData* getHeroDataById(int heroId);
	static HeroData* getHeroDataById(const string& heroId);
	static CityStatusData* getCityStatusDataById(int cityStatusId);
	static CityStatusData* getCityStatusDataById(const string& cityStatusId);
	static bool saveData(int index);
	static bool loadData(int index);
	static bool clearData();
};
#endif
