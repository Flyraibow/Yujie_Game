/*
This file (GoodsData.cpp) is generated
*/
#include "GoodsData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;

map<string, GoodsData*>* GoodsData::p_sharedDictionary = nullptr;

string GoodsData::getGoodsId() const
{
	return p_goodsId;
}

string GoodsData::getGoodsName() const
{
	string localId = "goods_goodsName_" + p_goodsId;
	return LocalizationHelper::getLocalization(localId);
}

GoodsCategoryData* GoodsData::getGoodsCategoryData() const
{
	return GoodsCategoryData::getGoodsCategoryDataById(p_categoryId);
}

string GoodsData::getCategoryId() const
{
	return p_categoryId;
}

cocos2d::Sprite* GoodsData::getIcon() const
{
	static const string s_basePath = "res/base/icon/goods/";
	string path = s_basePath + p_iconId;
	return cocos2d::Sprite::create(path);
}

string GoodsData::getIconId() const
{
	return p_iconId;
}

int GoodsData::getMaxPrice() const
{
	return p_maxPrice;
}

int GoodsData::getLevelUpExp() const
{
	return p_levelUpExp;
}

string GoodsData::getGoodsDescription() const
{
	string localId = "goods_goodsDescription_" + p_goodsId;
	return LocalizationHelper::getLocalization(localId);
}

string GoodsData::description() const
{
	string desc = "goodsData = {\n";
	desc += "\tgoodsId : " + to_string(p_goodsId) + "\n";
	desc += "\tgoodsName : " + getGoodsName() + "\n";
	desc += "\tcategoryId : " + to_string(p_categoryId) + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tmaxPrice : " + to_string(p_maxPrice) + "\n";
	desc += "\tlevelUpExp : " + to_string(p_levelUpExp) + "\n";
	desc += "\tgoodsDescription : " + getGoodsDescription() + "\n";
	desc += "}\n";
	return desc;
}

map<string, GoodsData*>* GoodsData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<string, GoodsData*>();
		static string resPath = "res/base/data/goods.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GoodsData* goodsData = new GoodsData();
				goodsData->p_goodsId = buffer->getString();
				goodsData->p_categoryId = buffer->getString();
				goodsData->p_iconId = buffer->getString();
				goodsData->p_maxPrice = buffer->getInt();
				goodsData->p_levelUpExp = buffer->getInt();
				p_sharedDictionary->insert(pair<string, GoodsData*>(goodsData->p_goodsId, goodsData));
			}
		}
	}
	return p_sharedDictionary;
}

GoodsData* GoodsData::getGoodsDataById(const string& goodsId)
{
	if (GoodsData::getSharedDictionary()->count(goodsId)) {
		return GoodsData::getSharedDictionary()->at(goodsId);
	}
	CCLOGERROR("invalid goodsId %s", goodsId.c_str());
	return nullptr;
}

