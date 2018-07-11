/*
This file (GoodsData.hpp) is generated at 2018-07-11 14:19:57
*/
#ifndef GoodsData_hpp
#define GoodsData_hpp
#include <unordered_map>
#include "GoodsCategoryData.hpp"

using namespace std;
class GoodsData
{
private:
	string p_goodsId;
	string p_categoryId;
	string p_iconId;
	int p_maxPrice;
	int p_levelUpExp;
public:
	string getGoodsId() const;
	string getGoodsName() const;
	GoodsCategoryData* getGoodsCategoryData() const;
	string getCategoryId() const;
	cocos2d::Sprite* getIcon() const;
	string getIconId() const;
	int getMaxPrice() const;
	int getLevelUpExp() const;
	string getGoodsDescription() const;
	string description() const;
	static unordered_map<string, GoodsData*>* getSharedDictionary();
	static GoodsData* getGoodsDataById(const string& goodsId);
};
#endif
