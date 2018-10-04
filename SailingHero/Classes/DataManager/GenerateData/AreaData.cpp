/*
This file (AreaData.cpp) is generated
*/
#include "AreaData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "LocalizationHelper.hpp"
#include "AreaData.hpp"
#include "AreaData.hpp"
#include "AreaData.hpp"
#include "AreaData.hpp"
#include "AreaData.hpp"
#include "AreaData.hpp"


using namespace SHUtil;

map<int, AreaData*>* AreaData::p_sharedDictionary = nullptr;

string AreaData::getId() const
{
	return to_string(p_areaId);
}

int AreaData::getAreaId() const
{
	return p_areaId;
}

string AreaData::getAreaName() const
{
	string localId = "area_areaName_" + to_string(p_areaId);
	return LocalizationHelper::getLocalization(localId);
}

cocos2d::Sprite* AreaData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/area/";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string AreaData::getIconPath()
{
	static const string s_basePath = "res/base/icon/area/";
	return s_basePath + p_iconId;
}

string AreaData::getIconId() const
{
	return p_iconId;
}

AreaData* AreaData::getLeftData() const
{
	return AreaData::getAreaDataById(p_leftId);
}

string AreaData::getLeftId() const
{
	return p_leftId;
}

AreaData* AreaData::getRightUpData() const
{
	return AreaData::getAreaDataById(p_rightUpId);
}

string AreaData::getRightUpId() const
{
	return p_rightUpId;
}

AreaData* AreaData::getRightData() const
{
	return AreaData::getAreaDataById(p_rightId);
}

string AreaData::getRightId() const
{
	return p_rightId;
}

AreaData* AreaData::getRightDownData() const
{
	return AreaData::getAreaDataById(p_rightDownId);
}

string AreaData::getRightDownId() const
{
	return p_rightDownId;
}

AreaData* AreaData::getUpData() const
{
	return AreaData::getAreaDataById(p_upId);
}

string AreaData::getUpId() const
{
	return p_upId;
}

AreaData* AreaData::getDownData() const
{
	return AreaData::getAreaDataById(p_downId);
}

string AreaData::getDownId() const
{
	return p_downId;
}

double AreaData::getX1() const
{
	return p_x1;
}

double AreaData::getX2() const
{
	return p_x2;
}

double AreaData::getY1() const
{
	return p_y1;
}

double AreaData::getY2() const
{
	return p_y2;
}

string AreaData::description() const
{
	string desc = "areaData = {\n";
	desc += "\tareaId : " + to_string(p_areaId) + "\n";
	desc += "\tareaName : " + getAreaName() + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tleft : " + to_string(p_leftId) + "\n";
	desc += "\trightUp : " + to_string(p_rightUpId) + "\n";
	desc += "\tright : " + to_string(p_rightId) + "\n";
	desc += "\trightDown : " + to_string(p_rightDownId) + "\n";
	desc += "\tup : " + to_string(p_upId) + "\n";
	desc += "\tdown : " + to_string(p_downId) + "\n";
	desc += "\tx1 : " + to_string(p_x1) + "\n";
	desc += "\tx2 : " + to_string(p_x2) + "\n";
	desc += "\ty1 : " + to_string(p_y1) + "\n";
	desc += "\ty2 : " + to_string(p_y2) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, AreaData*>* AreaData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, AreaData*>();
		static string resPath = "res/base/data/area.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				AreaData* areaData = new AreaData();
				areaData->p_areaId = buffer->getInt();
				areaData->p_iconId = buffer->getString();
				areaData->p_leftId = buffer->getString();
				areaData->p_rightUpId = buffer->getString();
				areaData->p_rightId = buffer->getString();
				areaData->p_rightDownId = buffer->getString();
				areaData->p_upId = buffer->getString();
				areaData->p_downId = buffer->getString();
				areaData->p_x1 = buffer->getDouble();
				areaData->p_x2 = buffer->getDouble();
				areaData->p_y1 = buffer->getDouble();
				areaData->p_y2 = buffer->getDouble();
				p_sharedDictionary->insert(pair<int, AreaData*>(areaData->p_areaId, areaData));
			}
		}
	}
	return p_sharedDictionary;
}

AreaData* AreaData::getAreaDataById(int areaId)
{
	if (AreaData::getSharedDictionary()->count(areaId)) {
		return AreaData::getSharedDictionary()->at(areaId);
	}
	return nullptr;
}

AreaData* AreaData::getAreaDataById(const string& areaId)
{
	if (areaId.length() == 0) return nullptr;
	return AreaData::getAreaDataById(atoi(areaId.c_str()));
}

string AreaData::getFieldValue(const string & fieldName)
{
	if (fieldName == "areaId") {
		return to_string(this->getAreaId());
	} else if (fieldName == "areaName") {
		return to_string(this->getAreaName());
	} else if (fieldName == "iconId") {
		return to_string(this->getIconId());
	} else if (fieldName == "left") {
		return to_string(this->getLeftId());
	} else if (fieldName == "rightUp") {
		return to_string(this->getRightUpId());
	} else if (fieldName == "right") {
		return to_string(this->getRightId());
	} else if (fieldName == "rightDown") {
		return to_string(this->getRightDownId());
	} else if (fieldName == "up") {
		return to_string(this->getUpId());
	} else if (fieldName == "down") {
		return to_string(this->getDownId());
	} else if (fieldName == "x1") {
		return to_string(this->getX1());
	} else if (fieldName == "x2") {
		return to_string(this->getX2());
	} else if (fieldName == "y1") {
		return to_string(this->getY1());
	} else if (fieldName == "y2") {
		return to_string(this->getY2());
	}
	CCLOGWARN("Couldn't recognize %s in AreaData", fieldName.c_str());
	return "";
}

