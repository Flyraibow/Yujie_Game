/*
This file (CategoryUpdateData.hpp) is generated
*/
#ifndef CategoryUpdateData_hpp
#define CategoryUpdateData_hpp
#include <map>
#include "BaseData.h"
#include <set>



class CategoryUpdateData: public BaseData
{
private:
	static map<int, CategoryUpdateData*>* p_sharedDictionary;
	int p_categoryUpdateId;
	set<int> p_updateMonth;
public:
	string getId() const;
	int getCategoryUpdateId() const;
	string getCategoryUpdateName() const;
	set<int> getUpdateMonth() const;
	string description() const;
	static map<int, CategoryUpdateData*>* getSharedDictionary();
	static CategoryUpdateData* getCategoryUpdateDataById(int categoryUpdateId);
	static CategoryUpdateData* getCategoryUpdateDataById(const string& categoryUpdateId);
};
#endif
