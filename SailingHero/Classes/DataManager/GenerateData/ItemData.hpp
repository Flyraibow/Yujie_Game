/*
This file (ItemData.hpp) is generated at 2018-07-11 01:50:01
*/
#ifndef ItemData_hpp
#define ItemData_hpp
#include <unordered_map>
#include "ItemCategoryData.hpp"

using namespace std;
class ItemData
{
private:
	string p_itemId;
	string p_iconId;
	string p_itemCategoryId;
	int p_value;
	int p_job;
	int p_price;
public:
	string getItemId() const;
	string getItemName() const;
	cocos2d::Sprite* getIcon() const;
	string getIconId() const;
	ItemCategoryData* getItemCategoryData() const;
	string getItemCategoryId() const;
	int getValue() const;
	int getJob() const;
	int getPrice() const;
	string getItemDescription() const;
	string description() const;
	static unordered_map<string, ItemData*>* getSharedDictionary();
	static ItemData* getItemDataById(const string& itemId);
};
#endif
