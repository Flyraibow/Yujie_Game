/*
This file (SystemButtonData.hpp) is generated
*/
#ifndef SystemButtonData_hpp
#define SystemButtonData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class SystemButtonData: public BaseData
{
private:
	static map<int, SystemButtonData*>* p_sharedDictionary;
	int p_buttonId;
public:
	string getId() const;
	int getButtonId() const;
	string getButtonName() const;
	string description() const;
	static map<int, SystemButtonData*>* getSharedDictionary();
	static SystemButtonData* getSystemButtonDataById(int buttonId);
	static SystemButtonData* getSystemButtonDataById(const string& buttonId);
};
#endif
