/*
This file (ShipSizeData.hpp) is generated
*/
#ifndef ShipSizeData_hpp
#define ShipSizeData_hpp
#include <map>
#include "BaseData.h"


class ShipSizeData: public BaseData
{
private:
	static map<int, ShipSizeData*>* p_sharedDictionary;
	int p_shipSizeId;
public:
	string getId() const;
	int getShipSizeId() const;
	string getShipSizeName() const;
	string description() const;
	static map<int, ShipSizeData*>* getSharedDictionary();
	static ShipSizeData* getShipSizeDataById(int shipSizeId);
	static ShipSizeData* getShipSizeDataById(const string& shipSizeId);
};
#endif
