/*
This file (ItemCategoryData.hpp) is generated at 2018-07-11 01:50:01
*/
#ifndef ItemCategoryData_hpp
#define ItemCategoryData_hpp
#include <unordered_map>

using namespace std;
class ItemCategoryData
{
private:
	string p_itemCategoryId;
public:
	string getItemCategoryId() const;
	string getItemCategoryName() const;
	string description() const;
	static unordered_map<string, ItemCategoryData*>* getSharedDictionary();
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
};
#endif
