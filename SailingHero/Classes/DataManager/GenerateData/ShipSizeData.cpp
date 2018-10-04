/*
This file (ShipSizeData.cpp) is generated
*/
#include "ShipSizeData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"


using namespace SHUtil;

map<int, ShipSizeData*>* ShipSizeData::p_sharedDictionary = nullptr;

string ShipSizeData::getId() const
{
	return to_string(p_shipSizeId);
}

int ShipSizeData::getShipSizeId() const
{
	return p_shipSizeId;
}

string ShipSizeData::getShipSizeName() const
{
	string localId = "shipSize_shipSizeName_" + to_string(p_shipSizeId);
	return LocalizationHelper::getLocalization(localId);
}

string ShipSizeData::description() const
{
	string desc = "shipSizeData = {\n";
	desc += "\tshipSizeId : " + to_string(p_shipSizeId) + "\n";
	desc += "\tshipSizeName : " + getShipSizeName() + "\n";
	desc += "}\n";
	return desc;
}

const map<int, ShipSizeData*>* ShipSizeData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ShipSizeData*>();
		static string resPath = "res/base/data/shipSize.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ShipSizeData* shipSizeData = new ShipSizeData();
				shipSizeData->p_shipSizeId = buffer->getInt();
				p_sharedDictionary->insert(pair<int, ShipSizeData*>(shipSizeData->p_shipSizeId, shipSizeData));
			}
		}
	}
	return p_sharedDictionary;
}

ShipSizeData* ShipSizeData::getShipSizeDataById(int shipSizeId)
{
	if (ShipSizeData::getSharedDictionary()->count(shipSizeId)) {
		return ShipSizeData::getSharedDictionary()->at(shipSizeId);
	}
	return nullptr;
}

ShipSizeData* ShipSizeData::getShipSizeDataById(const string& shipSizeId)
{
	if (shipSizeId.length() == 0) return nullptr;
	return ShipSizeData::getShipSizeDataById(atoi(shipSizeId.c_str()));
}

string ShipSizeData::getFieldValue(const string & fieldName)
{
	if (fieldName == "shipSizeId") {
		return to_string(this->getShipSizeId());
	} else if (fieldName == "shipSizeName") {
		return to_string(this->getShipSizeName());
	}
	CCLOGWARN("Couldn't recognize %s in ShipSizeData", fieldName.c_str());
	return "";
}

