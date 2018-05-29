//
//  GoodsData.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/28/18.
//

#ifndef GoodsData_hpp
#define GoodsData_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GoodsData
{
private:
    string s_goodsId;
    string s_goodsIconId;
    int s_maxGoodsPrice;
    int s_levelUpExp;
    static bool init();
public:
    string getGoodsId() const;
    string getGoodsName() const;
    Sprite* getGoodsIcon() const;
    int getMaxPrice() const;
    int getLevelUpExp() const;
    string getGoodsDescription() const;
    static GoodsData* getGoodsDataById(const string &goodsId);
};

#endif /* GoodsData_hpp */
