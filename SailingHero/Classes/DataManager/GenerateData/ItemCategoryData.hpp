/*
This file (ItemCategoryData.hpp) is generated
*/
#ifndef ItemCategoryData_hpp
#define ItemCategoryData_hpp
#include <map>
#include "BaseData.h"

using namespace std;
class ItemCategoryData: public BaseData
{
private:
	static map<string, ItemCategoryData*>* p_sharedDictionary;
	string p_itemCategoryId;
public:
	string getId() const;
	string getItemCategoryId() const;
	string getItemCategoryName() const;
	string description() const;
	static map<string, ItemCategoryData*>* getSharedDictionary();
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
};
#endif
