/*
This file (GenderData.hpp) is generated at 2018-06-27 22:21:10
*/
#ifndef GenderData_hpp
#define GenderData_hpp
#include <unordered_map>

using namespace std;
class GenderData
{
private:
	string p_genderId;
public:
	string getGenderId() const;
	string getGenderName() const;
	string description() const;
	static unordered_map<string, GenderData*>* getSharedDictionary();
	static GenderData* getGenderDataById(const string& genderId);
};
#endif
