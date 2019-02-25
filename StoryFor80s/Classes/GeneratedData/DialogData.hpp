/*
This file (DialogData.hpp) is generated
*/
#ifndef DialogData_hpp
#define DialogData_hpp
#include <map>
#include "BaseData.h"
#include <vector>
#include "FriendData.hpp"


class DialogData: public BaseData
{
private:
	static map<string, DialogData*>* p_sharedDictionary;
	string p_dialogId;
	string p_friendId;
	string p_name;
	vector<string> p_parameters;
public:
	string getId() const;
	string getDialogId() const;
	FriendData* getFriendData() const;
	string getFriendId() const;
	string getName() const;
	string getContent() const;
	vector<string> getParameters() const;
	string description() const;
	static const map<string, DialogData*>* getSharedDictionary();
	static DialogData* getDialogDataById(const string& dialogId);
	string getFieldValue(const string & fieldName);
};
#endif
