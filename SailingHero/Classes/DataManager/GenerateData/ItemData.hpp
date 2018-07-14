/*
This file (ItemData.hpp) is generated
*/
#ifndef ItemData_hpp
#define ItemData_hpp
#include <map>
#include "ItemCategoryData.hpp"

using namespace std;
class ItemData
{
private:
	static map<string, ItemData*>* p_sharedDictionary;
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
	static map<string, ItemData*>* getSharedDictionary();
	static ItemData* getItemDataById(const string& itemId);
};
#endif
