/*
This file (CultureData.hpp) is generated
*/
#ifndef CultureData_hpp
#define CultureData_hpp
#include <map>
#include "BaseData.h"


using namespace std;
class CultureData: public BaseData
{
private:
	static map<int, CultureData*>* p_sharedDictionary;
	int p_cutureId;
	string p_oceanMusicId;
	string p_cityMusicId;
	string p_plazaStoreIconId;
	string p_plazaBuildingIconId;
public:
	string getId() const;
	int getCutureId() const;
	string getCultureName() const;
	string getOceanMusicPath() const;
	string getOceanMusicId() const;
	string getCityMusicPath() const;
	string getCityMusicId() const;
	cocos2d::Sprite* getPlazaStoreIcon(bool isDefaultSize = true);
	string getPlazaStoreIconId() const;
	cocos2d::Sprite* getPlazaBuildingIcon(bool isDefaultSize = true);
	string getPlazaBuildingIconId() const;
	string description() const;
	static map<int, CultureData*>* getSharedDictionary();
	static CultureData* getCultureDataById(int cutureId);
	static CultureData* getCultureDataById(const string& cutureId);
};
#endif
