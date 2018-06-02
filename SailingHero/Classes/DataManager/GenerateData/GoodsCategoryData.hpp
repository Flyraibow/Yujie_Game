/*
This file (GoodsCategoryData.hpp) is generated at 2018-06-02 00:14:16
*/
#ifndef GoodsCategoryData_hpp
#define GoodsCategoryData_hpp
#include <unordered_map>
#include "CategoryUpdateData.hpp"

using namespace std;
class GoodsCategoryData
{
private:
	string p_categoryId;
	string p_categoryUpdateId;
public:
	string getCategoryId() const;
	string getCategory_name() const;
	CategoryUpdateData* getCategoryUpdateData() const;
	string getCategoryUpdateId() const;
	string description() const;
	static unordered_map<string, GoodsCategoryData*>* getSharedDictionary();
	static GoodsCategoryData* getGoodsCategoryDataById(const string& categoryId);
};
#endif
