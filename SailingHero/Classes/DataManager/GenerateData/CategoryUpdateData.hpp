/*
This file (CategoryUpdateData.hpp) is generated
*/
#ifndef CategoryUpdateData_hpp
#define CategoryUpdateData_hpp
#include <map>
#include <unordered_set>

using namespace std;
class CategoryUpdateData
{
private:
	static map<string, CategoryUpdateData*>* p_sharedDictionary;
	string p_categoryUpdateId;
	unordered_set<int> p_updateMonth;
public:
	string getCategoryUpdateId() const;
	string getCategoryUpdateName() const;
	unordered_set<int> getUpdateMonth() const;
	string description() const;
	static map<string, CategoryUpdateData*>* getSharedDictionary();
	static CategoryUpdateData* getCategoryUpdateDataById(const string& categoryUpdateId);
};
#endif
