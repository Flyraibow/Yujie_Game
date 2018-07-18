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
