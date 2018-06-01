//
//  GoodsData.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/28/18.
//

#ifndef GoodsData_hpp
#define GoodsData_hpp

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GoodsData
{
private:
    string s_goodsId;
    string s_goodsIconId;
    string s_goodsTypeId;
    int s_maxGoodsPrice;
    int s_levelUpExp;
    static bool init();
public:
    string getGoodsId() const;
    string getGoodsName() const;
    string getGoodsTypeId() const;
    Sprite* getGoodsIcon() const;
    int getMaxPrice() const;
    int getLevelUpExp() const;
    string getGoodsDescription() const;
    string description() const;
    static GoodsData* getGoodsDataById(const string &goodsId);
};

#endif /* GoodsData_hpp */
