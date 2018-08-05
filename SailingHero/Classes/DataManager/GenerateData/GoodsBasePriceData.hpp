/*
This file (GoodsBasePriceData.hpp) is generated
*/
#ifndef GoodsBasePriceData_hpp
#define GoodsBasePriceData_hpp
#include <map>


using namespace std;
class GoodsBasePriceData
{
private:
	static map<int, map<int,int>>* p_sharedDictionary;
public:
	static const map<int, map<int,int>>* getSharedDictionary();
	static int getGoodsBasePrice(int goodsId, int cultureId);
};
#endif
