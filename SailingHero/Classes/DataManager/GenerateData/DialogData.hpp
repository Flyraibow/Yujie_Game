/*
This file (DialogData.hpp) is generated
*/
#ifndef DialogData_hpp
#define DialogData_hpp
#include <map>
#include "BaseData.h"
#include "HeroData.hpp"


class DialogData: public BaseData
{
private:
	static map<string, DialogData*>* p_sharedDictionary;
	string p_dialogId;
	bool p_showFullNames;
	bool p_showImage;
	string p_heroIdId;
public:
	string getId() const;
	string getDialogId() const;
	bool getShowFullNames() const;
	bool getShowImage() const;
	HeroData* getHeroIdData() const;
	string getHeroIdId() const;
	string getDialogContent() const;
	string description() const;
	static const map<string, DialogData*>* getSharedDictionary();
	static DialogData* getDialogDataById(const string& dialogId);
	string getFieldValue(const string & fieldName);
};
#endif
