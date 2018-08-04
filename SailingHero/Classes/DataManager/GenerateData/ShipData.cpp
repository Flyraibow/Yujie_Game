/*
This file (ShipData.cpp) is generated
*/
#include "ShipData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, ShipData*>* ShipData::p_sharedDictionary = nullptr;

string ShipData::getId() const
{
	return to_string(p_cannonId);
}

int ShipData::getCannonId() const
{
	return p_cannonId;
}

string ShipData::getCannonName() const
{
	string localId = "ship_cannonName_" + to_string(p_cannonId);
	return LocalizationHelper::getLocalization(localId);
}

string ShipData::getCannonDescription() const
{
	string localId = "ship_cannonDescription_" + to_string(p_cannonId);
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* ShipData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/cannon";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string ShipData::getIconPath()
{
	static const string s_basePath = "res/base/icon/cannon";
	return s_basePath + p_iconId;
}

string ShipData::getIconId() const
{
	return p_iconId;
}

int ShipData::getMilltaryValue() const
{
	return p_milltaryValue;
}

int ShipData::getPrice() const
{
	return p_price;
}

int ShipData::getRange() const
{
	return p_range;
}

int ShipData::getPower() const
{
	return p_power;
}

string ShipData::description() const
{
	string desc = "shipData = {\n";
	desc += "\tcannonId : " + to_string(p_cannonId) + "\n";
	desc += "\tcannonName : " + getCannonName() + "\n";
	desc += "\tcannonDescription : " + getCannonDescription() + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tmilltaryValue : " + to_string(p_milltaryValue) + "\n";
	desc += "\tprice : " + to_string(p_price) + "\n";
	desc += "\trange : " + to_string(p_range) + "\n";
	desc += "\tpower : " + to_string(p_power) + "\n";
	desc += "}\n";
	return desc;
}

map<int, ShipData*>* ShipData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, ShipData*>();
		static string resPath = "res/base/data/ship.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				ShipData* shipData = new ShipData();
				shipData->p_cannonId = buffer->getInt();
				shipData->p_iconId = buffer->getString();
				shipData->p_milltaryValue = buffer->getInt();
				shipData->p_price = buffer->getInt();
				shipData->p_range = buffer->getInt();
				shipData->p_power = buffer->getInt();
				p_sharedDictionary->insert(pair<int, ShipData*>(shipData->p_cannonId, shipData));
			}
		}
	}
	return p_sharedDictionary;
}

ShipData* ShipData::getShipDataById(int cannonId)
{
	if (ShipData::getSharedDictionary()->count(cannonId)) {
		return ShipData::getSharedDictionary()->at(cannonId);
	}
	return nullptr;
}

ShipData* ShipData::getShipDataById(const string& cannonId)
{
	if (cannonId.length() == 0) return nullptr;
	return ShipData::getShipDataById(atoi(cannonId.c_str()));
}

