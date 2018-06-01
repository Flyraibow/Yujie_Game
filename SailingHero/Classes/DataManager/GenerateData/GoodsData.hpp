/*
This file (GoodsData.hpp) is generated at 2018-06-01 16:39:56
*/
#ifndef GoodsData_hpp
#define GoodsData_hpp
#include <unordered_map>

using namespace std;
class GoodsData
{
private:
	string p_goodsId;
	string p_type;
	string p_iconId;
	int p_maxPrice;
	int p_levelUpExp;
public:
	string getGoodsId() const;
	string getGoodsName() const;
	string getType() const;
	string getIconId() const;
	int getMaxPrice() const;
	int getLevelUpExp() const;
	string getGoodsDescription() const;
	string description() const;
	static unordered_map<string, GoodsData*>* getSharedDictionary();
	static GoodsData* getGoodsDataById(const string& goodsId);
};
#endif
