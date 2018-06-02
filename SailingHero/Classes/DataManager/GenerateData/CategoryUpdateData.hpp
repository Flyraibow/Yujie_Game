/*
This file (CategoryUpdateData.hpp) is generated at 2018-06-02 00:14:16
*/
#ifndef CategoryUpdateData_hpp
#define CategoryUpdateData_hpp
#include <unordered_map>
#include <unordered_set>

using namespace std;
class CategoryUpdateData
{
private:
	string p_categoryUpdateId;
	unordered_set<int> p_updateMonth;
public:
	string getCategoryUpdateId() const;
	string getCategoryUpdateName() const;
	unordered_set<int> getUpdateMonth() const;
	string description() const;
	static unordered_map<string, CategoryUpdateData*>* getSharedDictionary();
	static CategoryUpdateData* getCategoryUpdateDataById(const string& categoryUpdateId);
};
#endif
