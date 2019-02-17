/*
This file (ItemData.hpp) is generated
*/
#ifndef ItemData_hpp
#define ItemData_hpp
#include <map>
#include "BaseData.h"
#include "ItemCategoryData.hpp"


class ItemData: public BaseData
{
private:
	static map<string, ItemData*>* p_sharedDictionary;
	string p_itemId;
	string p_categoryId;
	int p_price;
	int p_number;
public:
	string getId() const;
	string getItemId() const;
	string getName() const;
	ItemCategoryData* getCategoryData() const;
	string getCategoryId() const;
	int getPrice() const;
	int getNumber() const;
	void setNumber(int number);
	string description() const;
	static const map<string, ItemData*>* getSharedDictionary();
	static ItemData* getItemDataById(const string& itemId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName);
};
#endif
