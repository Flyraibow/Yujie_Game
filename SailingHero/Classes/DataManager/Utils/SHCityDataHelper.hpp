//
//  SHCityDataHelper.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#ifndef SHCityDataHelper_hpp
#define SHCityDataHelper_hpp

#include <stdio.h>
#include "CityData.hpp"
#include "ItemData.hpp"
#include "GoodsData.hpp"
#include "GuildData.hpp"
#include <vector>

using namespace std;

bool enableGoodsInCity(CityData* cityData, GoodsData* goodsData);
vector<pair<GuildData *,int>> getOrderedCityGuildShares(CityData* cityData);


#endif /* SHCityDataHelper_hpp */
