/*
This file (GoodsCategoryData.hpp) is generated
*/
#ifndef GoodsCategoryData_hpp
#define GoodsCategoryData_hpp
#include <map>
#include "BaseData.h"
#include "CategoryUpdateData.hpp"

using namespace std;
class GoodsCategoryData: public BaseData
{
private:
	static map<int, GoodsCategoryData*>* p_sharedDictionary;
	int p_categoryId;
	string p_categoryUpdateId;
public:
	string getId() const;
	int getCategoryId() const;
	string getCategory_name() const;
	CategoryUpdateData* getCategoryUpdateData() const;
	string getCategoryUpdateId() const;
	string description() const;
	static map<int, GoodsCategoryData*>* getSharedDictionary();
	static GoodsCategoryData* getGoodsCategoryDataById(int categoryId);
	static GoodsCategoryData* getGoodsCategoryDataById(const string& categoryId);
};
#endif
