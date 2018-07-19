//
//  SHCityDataHelper.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#include "SHCityDataHelper.hpp"


bool enableGoodsInCity(CityData* cityData, GoodsData* goodsData)
{
  for (auto cityGoodsData : cityData->getCityGoodsDataVector()) {
    if (cityGoodsData->getGoodsId() == goodsData->getId() && cityGoodsData->getIsHidden()) {
      cityGoodsData->setIsHidden(false);
      return true;
    }
  }
  return false;
}


vector<pair<GuildData *,int>> getOrderedCityGuildShares(CityData* cityData)
{
  auto guildMap = cityData->getGuildShareMap();
  typedef function<bool(pair<string, int>, pair<string, int>)>  Comparator;
  Comparator compFunctor =
  [](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
  {
    return elem1.second > elem2.second;
  };
  set<pair<string, int>, Comparator> setOfWords(guildMap.begin(), guildMap.end(), compFunctor);
  vector<pair<GuildData*, int>> result;
  for (std::pair<std::string, int> element : setOfWords) {
    result.push_back(make_pair(GuildData::getGuildDataById(element.first), element.second));
  }
  return result;
}
