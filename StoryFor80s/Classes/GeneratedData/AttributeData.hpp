/*
This file (AttributeData.hpp) is generated
*/
#ifndef AttributeData_hpp
#define AttributeData_hpp
#include <map>
#include "BaseData.h"


class AttributeData: public BaseData
{
private:
	static map<string, AttributeData*>* p_sharedDictionary;
	string p_attributeId;
	int p_value;
public:
	string getId() const;
	string getAttributeId() const;
	string getName() const;
	int getValue() const;
	void setValue(int value);
	string description() const;
	static const map<string, AttributeData*>* getSharedDictionary();
	static AttributeData* getAttributeDataById(const string& attributeId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
};
#endif
