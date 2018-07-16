/*
This file (CategoryUpdateData.hpp) is generated
*/
#ifndef CategoryUpdateData_hpp
#define CategoryUpdateData_hpp
#include <map>
#include "BaseData.h"
#include <set>

using namespace std;
class CategoryUpdateData: public BaseData
{
private:
	static map<string, CategoryUpdateData*>* p_sharedDictionary;
	string p_categoryUpdateId;
	set<int> p_updateMonth;
public:
	string getId() const;
	string getCategoryUpdateId() const;
	string getCategoryUpdateName() const;
	set<int> getUpdateMonth() const;
	string description() const;
	static map<string, CategoryUpdateData*>* getSharedDictionary();
	static CategoryUpdateData* getCategoryUpdateDataById(const string& categoryUpdateId);
};
#endif
