/*
This file (ParentChatData.hpp) is generated
*/
#ifndef ParentChatData_hpp
#define ParentChatData_hpp
#include <map>
#include "BaseData.h"


class ParentChatData: public BaseData
{
private:
	static map<string, ParentChatData*>* p_sharedDictionary;
	string p_chatId;
public:
	string getId() const;
	string getChatId() const;
	string getName() const;
	string description() const;
	static const map<string, ParentChatData*>* getSharedDictionary();
	static ParentChatData* getParentChatDataById(const string& chatId);
	string getFieldValue(const string & fieldName);
	BaseData* getDataByField(const string & fieldName);
};
#endif
