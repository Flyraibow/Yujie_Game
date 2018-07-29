/*
This file (CityGoodsData.hpp) is generated
*/
#ifndef CityGoodsData_hpp
#define CityGoodsData_hpp
#include <map>
#include "BaseData.h"
#include "GoodsData.hpp"


class CityGoodsData: public BaseData
{
private:
	static map<int, CityGoodsData*>* p_sharedDictionary;
	int p_cityGoodsId;
	string p_goodsId;
	int p_commercialRequirement;
	int p_basePrice;
	int p_abundance;
	bool p_isHidden;
public:
	string getId() const;
	int getCityGoodsId() const;
	GoodsData* getGoodsData() const;
	string getGoodsId() const;
	int getCommercialRequirement() const;
	int getBasePrice() const;
	int getAbundance() const;
	void setAbundance(int abundance);
	bool getIsHidden() const;
	void setIsHidden(bool isHidden);
	string description() const;
	static map<int, CityGoodsData*>* getSharedDictionary();
	static CityGoodsData* getCityGoodsDataById(int cityGoodsId);
	static CityGoodsData* getCityGoodsDataById(const string& cityGoodsId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
};
#endif
