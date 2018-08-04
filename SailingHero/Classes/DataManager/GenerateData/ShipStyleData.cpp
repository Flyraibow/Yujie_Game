/*
This file (ShipStyleData.cpp) is generated
*/
#include "ShipStyleData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, ShipStyleData*>* ShipStyleData::p_sharedDictionary = nullptr;

string ShipStyleData::getId() const
{
	return to_string(p_shipStyleId);
}

int ShipStyleData::getShipStyleId() const
{
	return p_shipStyleId;
}

string ShipStyleData::getShipStyleName() const
{
	string localId = "shipStyle_shipStyleName_" + to_string(p_shipStyleId);
	return LocalizationHelper::getLocalization(localId);
}

ShipSizeData* ShipStyleData::getShipSizeData() const
{
	return ShipSizeData::getShipSizeDataById(p_shipSizeId);
}

string ShipStyleData::getShipSizeId() const
{
	return p_shipSizeId;
}

cocos2d::Sprite* ShipStyleData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/ship";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string ShipStyleData::getIconPath()
{
	static const string s_basePath = "res/base/icon/ship";
	return s_basePath + p_iconId;
}

string ShipStyleData::getIconId() const
{
	return p_iconId;
}

int ShipStyleData::getDevelopValue() const
{
	return p_developValue;
}

int ShipStyleData::getPrice() const
{
	return p_price;
}

int ShipStyleData::getDuration() const
{
	return p_duration;
}

set<CultureData*> ShipStyleData::getSellCultureDataSet() const
{
	set<CultureData*> resultSet;
	for (auto objId : p_sellCultureIdSet) {
		resultSet.insert(CultureData::getCultureDataById(objId));
	}
	return resultSet;
}

set<string> ShipStyleData::getSellCultureIdSet() const
{
	return p_sellCultureIdSet;
}

string ShipStyleData::description() const
{
	string desc = "shipStyleData = {\n";
	desc += "\tshipStyleId : " + to_string(p_shipStyleId) + "\n";
	desc += "\tshipStyleName : " + getShipStyleName() + "\n";
	desc += "\tshipSize : " + to_string(p_shipSizeId) + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tdevelopValue : " + to_string(p_developValue) + "\n";
	desc += "\tprice : " + to_string(p_price) + "\n";
	desc += "\tduration : " + to_string(p_duration) + "\n";
	desc += "\tsellCulture : " + to_string(p_sellCultureIdSet) + "\n";
	desc += "}\n";
	return desc;
}

map<int, ShipStyleData*>* ShipStyleData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ShipStyleData*>();
		static string resPath = "res/base/data/shipStyle.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ShipStyleData* shipStyleData = new ShipStyleData();
				shipStyleData->p_shipStyleId = buffer->getInt();
				shipStyleData->p_shipSizeId = buffer->getString();
				shipStyleData->p_iconId = buffer->getString();
				shipStyleData->p_developValue = buffer->getInt();
				shipStyleData->p_price = buffer->getInt();
				shipStyleData->p_duration = buffer->getInt();
				auto sellCultureCount = buffer->getLong();
				for (int j = 0; j < sellCultureCount; ++j) {
					shipStyleData->p_sellCultureIdSet.insert(buffer->getString());
				}
				p_sharedDictionary->insert(pair<int, ShipStyleData*>(shipStyleData->p_shipStyleId, shipStyleData));
			}
		}
	}
	return p_sharedDictionary;
}

ShipStyleData* ShipStyleData::getShipStyleDataById(int shipStyleId)
{
	if (ShipStyleData::getSharedDictionary()->count(shipStyleId)) {
		return ShipStyleData::getSharedDictionary()->at(shipStyleId);
	}
	return nullptr;
}

ShipStyleData* ShipStyleData::getShipStyleDataById(const string& shipStyleId)
{
	if (shipStyleId.length() == 0) return nullptr;
	return ShipStyleData::getShipStyleDataById(atoi(shipStyleId.c_str()));
}

