/*
This file (ItemCategoryData.hpp) is generated
*/
#ifndef ItemCategoryData_hpp
#define ItemCategoryData_hpp
#include <map>
#include "BaseData.h"



class ItemCategoryData: public BaseData
{
private:
	static map<int, ItemCategoryData*>* p_sharedDictionary;
	int p_itemCategoryId;
public:
	string getId() const;
	int getItemCategoryId() const;
	string getItemCategoryName() const;
	string description() const;
	static map<int, ItemCategoryData*>* getSharedDictionary();
	static ItemCategoryData* getItemCategoryDataById(int itemCategoryId);
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
};
#endif
