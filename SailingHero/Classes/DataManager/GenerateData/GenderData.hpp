/*
This file (GenderData.hpp) is generated
*/
#ifndef GenderData_hpp
#define GenderData_hpp
#include <unordered_map>

using namespace std;
class GenderData
{
private:
	static unordered_map<string, GenderData*>* p_sharedDictionary;
	string p_genderId;
public:
	string getGenderId() const;
	string getGenderName() const;
	string description() const;
	static unordered_map<string, GenderData*>* getSharedDictionary();
	static GenderData* getGenderDataById(const string& genderId);
};
#endif
