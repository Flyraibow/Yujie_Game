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
	string p_condition;
	string p_categoryId;
	int p_price;
	bool p_haveIt;
public:
	string getId() const;
	string getItemId() const;
	string getName() const;
	string getCondition() const;
	ItemCategoryData* getCategoryData() const;
	string getCategoryId() const;
	int getPrice() const;
	bool getHaveIt() const;
	void setHaveIt(bool haveIt);
	string description() const;
	static const map<string, ItemData*>* getSharedDictionary();
	static ItemData* getItemDataById(const string& itemId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
