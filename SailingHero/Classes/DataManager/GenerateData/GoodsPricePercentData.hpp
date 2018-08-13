/*
This file (GoodsPricePercentData.hpp) is generated
*/
#ifndef GoodsPricePercentData_hpp
#define GoodsPricePercentData_hpp
#include <map>


using namespace std;
class GoodsPricePercentData
{
private:
	static map<int, map<int,int>>* p_sharedDictionary;
public:
	static const map<int, map<int,int>>* getSharedDictionary();
	static int getGoodsPricePercent(int cityId, int goodsCategoryId);
	static void setGoodsPricePercent(int cityId, int goodsCategoryId, int value);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
