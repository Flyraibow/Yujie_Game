/*
This file (ItemCategoryData.hpp) is generated
*/
#ifndef ItemCategoryData_hpp
#define ItemCategoryData_hpp
#include <unordered_map>

using namespace std;
class ItemCategoryData
{
private:
	static unordered_map<string, ItemCategoryData*>* p_sharedDictionary;
	string p_itemCategoryId;
public:
	string getItemCategoryId() const;
	string getItemCategoryName() const;
	string description() const;
	static unordered_map<string, ItemCategoryData*>* getSharedDictionary();
	static ItemCategoryData* getItemCategoryDataById(const string& itemCategoryId);
};
#endif
