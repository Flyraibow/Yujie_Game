/*
This file (GoodsData.hpp) is generated
*/
#ifndef GoodsData_hpp
#define GoodsData_hpp
#include <map>
#include "GoodsCategoryData.hpp"

using namespace std;
class GoodsData
{
private:
	static map<string, GoodsData*>* p_sharedDictionary;
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
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconId() const;
	int getMaxPrice() const;
	int getLevelUpExp() const;
	string getGoodsDescription() const;
	string description() const;
	static map<string, GoodsData*>* getSharedDictionary();
	static GoodsData* getGoodsDataById(const string& goodsId);
};
#endif
