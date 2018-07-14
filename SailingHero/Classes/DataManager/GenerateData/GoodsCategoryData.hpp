/*
This file (GoodsCategoryData.hpp) is generated
*/
#ifndef GoodsCategoryData_hpp
#define GoodsCategoryData_hpp
#include <map>
#include "CategoryUpdateData.hpp"

using namespace std;
class GoodsCategoryData
{
private:
	static map<string, GoodsCategoryData*>* p_sharedDictionary;
	string p_categoryId;
	string p_categoryUpdateId;
public:
	string getCategoryId() const;
	string getCategory_name() const;
	CategoryUpdateData* getCategoryUpdateData() const;
	string getCategoryUpdateId() const;
	string description() const;
	static map<string, GoodsCategoryData*>* getSharedDictionary();
	static GoodsCategoryData* getGoodsCategoryDataById(const string& categoryId);
};
#endif
