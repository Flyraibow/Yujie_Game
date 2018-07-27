/*
This file (GoodsData.hpp) is generated
*/
#ifndef GoodsData_hpp
#define GoodsData_hpp
#include <map>
#include "BaseData.h"
#include "GoodsCategoryData.hpp"
#include "ItemData.hpp"



class GoodsData: public BaseData
{
private:
	static map<int, GoodsData*>* p_sharedDictionary;
	int p_goodsId;
	string p_categoryId;
	string p_iconId;
	int p_maxPrice;
	string p_unlockItemId;
	int p_levelUpExp;
public:
	string getId() const;
	int getGoodsId() const;
	string getGoodsName() const;
	GoodsCategoryData* getCategoryData() const;
	string getCategoryId() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconId() const;
	int getMaxPrice() const;
	ItemData* getUnlockItemData() const;
	string getUnlockItemId() const;
	int getLevelUpExp() const;
	string getGoodsDescription() const;
	string description() const;
	static map<int, GoodsData*>* getSharedDictionary();
	static GoodsData* getGoodsDataById(int goodsId);
	static GoodsData* getGoodsDataById(const string& goodsId);
};
#endif
