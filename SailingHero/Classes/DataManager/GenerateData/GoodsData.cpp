/*
This file (GoodsData.cpp) is generated
*/
#include "GoodsData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, GoodsData*>* GoodsData::p_sharedDictionary = nullptr;

string GoodsData::getId() const
{
	return to_string(p_goodsId);
}

int GoodsData::getGoodsId() const
{
	return p_goodsId;
}

string GoodsData::getGoodsName() const
{
	string localId = "goods_goodsName_" + to_string(p_goodsId);
	return LocalizationHelper::getLocalization(localId);
}

GoodsCategoryData* GoodsData::getCategoryData() const
{
	return GoodsCategoryData::getGoodsCategoryDataById(p_categoryId);
}

string GoodsData::getCategoryId() const
{
	return p_categoryId;
}

cocos2d::Sprite* GoodsData::getIcon(bool isDefaultSize)
{
	static const string s_basePath = "res/base/icon/goods/";
	string path = s_basePath + p_iconId;
	auto icon = cocos2d::Sprite::create(path);
	if (!isDefaultSize) {
		icon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());
	}
	return icon;
}

string GoodsData::getIconPath()
{
	static const string s_basePath = "res/base/icon/goods/";
	return s_basePath + p_iconId;
}

string GoodsData::getIconId() const
{
	return p_iconId;
}

int GoodsData::getMaxPrice() const
{
	return p_maxPrice;
}

ItemData* GoodsData::getUnlockItemData() const
{
	return ItemData::getItemDataById(p_unlockItemId);
}

string GoodsData::getUnlockItemId() const
{
	return p_unlockItemId;
}

int GoodsData::getLevelUpExp() const
{
	return p_levelUpExp;
}

string GoodsData::getGoodsDescription() const
{
	string localId = "goods_goodsDescription_" + to_string(p_goodsId);
	return LocalizationHelper::getLocalization(localId);
}

string GoodsData::description() const
{
	string desc = "goodsData = {\n";
	desc += "\tgoodsId : " + to_string(p_goodsId) + "\n";
	desc += "\tgoodsName : " + getGoodsName() + "\n";
	desc += "\tcategory : " + to_string(p_categoryId) + "\n";
	desc += "\ticonId : " + to_string(p_iconId) + "\n";
	desc += "\tmaxPrice : " + to_string(p_maxPrice) + "\n";
	desc += "\tunlockItem : " + to_string(p_unlockItemId) + "\n";
	desc += "\tlevelUpExp : " + to_string(p_levelUpExp) + "\n";
	desc += "\tgoodsDescription : " + getGoodsDescription() + "\n";
	desc += "}\n";
	return desc;
}

const map<int, GoodsData*>* GoodsData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, GoodsData*>();
		static string resPath = "res/base/data/goods.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GoodsData* goodsData = new GoodsData();
				goodsData->p_goodsId = buffer->getInt();
				goodsData->p_categoryId = buffer->getString();
				goodsData->p_iconId = buffer->getString();
				goodsData->p_maxPrice = buffer->getInt();
				goodsData->p_unlockItemId = buffer->getString();
				goodsData->p_levelUpExp = buffer->getInt();
				p_sharedDictionary->insert(pair<int, GoodsData*>(goodsData->p_goodsId, goodsData));
			}
		}
	}
	return p_sharedDictionary;
}

GoodsData* GoodsData::getGoodsDataById(int goodsId)
{
	if (GoodsData::getSharedDictionary()->count(goodsId)) {
		return GoodsData::getSharedDictionary()->at(goodsId);
	}
	return nullptr;
}

GoodsData* GoodsData::getGoodsDataById(const string& goodsId)
{
	if (goodsId.length() == 0) return nullptr;
	return GoodsData::getGoodsDataById(atoi(goodsId.c_str()));
}

