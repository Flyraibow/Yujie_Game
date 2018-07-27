/*
This file (ItemData.hpp) is generated
*/
#ifndef ItemData_hpp
#define ItemData_hpp
#include <map>
#include "BaseData.h"
#include "ItemCategoryData.hpp"


using namespace std;
class ItemData: public BaseData
{
private:
	static map<int, ItemData*>* p_sharedDictionary;
	int p_itemId;
	string p_iconId;
	string p_itemCategoryId;
	int p_value;
	int p_job;
	int p_price;
public:
	string getId() const;
	int getItemId() const;
	string getItemName() const;
	cocos2d::Sprite* getIcon(bool isDefaultSize = true);
	string getIconPath();
	string getIconId() const;
	ItemCategoryData* getItemCategoryData() const;
	string getItemCategoryId() const;
	int getValue() const;
	int getJob() const;
	int getPrice() const;
	string getItemDescription() const;
	string description() const;
	static map<int, ItemData*>* getSharedDictionary();
	static ItemData* getItemDataById(int itemId);
	static ItemData* getItemDataById(const string& itemId);
};
#endif
