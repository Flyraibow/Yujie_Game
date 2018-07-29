/*
This file (TownPhotoData.hpp) is generated
*/
#ifndef TownPhotoData_hpp
#define TownPhotoData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class TownPhotoData: public BaseData
{
private:
	static map<string, TownPhotoData*>* p_sharedDictionary;
	string p_townPhotoId;
	string p_townPhotoImageId;
public:
	string getId() const;
	string getTownPhotoId() const;
	cocos2d::Sprite* getTownPhotoImage(bool isDefaultSize = true);
	string getTownPhotoImagePath();
	string getTownPhotoImageId() const;
	string description() const;
	static map<string, TownPhotoData*>* getSharedDictionary();
	static TownPhotoData* getTownPhotoDataById(const string& townPhotoId);
};
#endif
