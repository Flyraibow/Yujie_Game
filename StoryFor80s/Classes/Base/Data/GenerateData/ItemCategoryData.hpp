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
	static map<string, ItemCategoryData*>* p_sharedDictionary;
	string p_itemCategoryId;
public:
	string getId() const;
	string getItemCategoryId() const;
	string getName() const;
	string description() const;
	static const map<string, ItemCategoryData*>* getSharedDictionary();
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
	string getFieldValue(const string & fieldName);
};
#endif
