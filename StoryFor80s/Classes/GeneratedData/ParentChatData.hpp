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
	string p_condition;
	bool p_repeat;
	bool p_experienced;
	string p_story;
public:
	string getId() const;
	string getChatId() const;
	string getCondition() const;
	bool getRepeat() const;
	bool getExperienced() const;
	void setExperienced(bool experienced);
	string getStory() const;
	string description() const;
	static const map<string, ParentChatData*>* getSharedDictionary();
	static ParentChatData* getParentChatDataById(const string& chatId);
	static bool saveData(const string & path);
	static bool loadData(const string & path);
	static bool clearData();
	void setFieldValue(const string & fieldName, const string & value);
	string getFieldValue(const string & fieldName) const;
	BaseData* getDataByField(const string & fieldName) const;
	vector<BaseData *> getFieldDataList(const string & fieldName) const;
};
#endif
