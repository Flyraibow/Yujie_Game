/*
This file (CultureData.hpp) is generated
*/
#ifndef CultureData_hpp
#define CultureData_hpp
#include <map>

using namespace std;
class CultureData
{
private:
	static map<string, CultureData*>* p_sharedDictionary;
	string p_cutureId;
	string p_oceanMusicId;
	string p_cityMusicId;
	string p_plazaStoreIconId;
	string p_plazaBuildingIconId;
public:
	string getCutureId() const;
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
	static map<string, CultureData*>* getSharedDictionary();
	static CultureData* getCultureDataById(const string& cutureId);
};
#endif
