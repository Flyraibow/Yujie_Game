/*
This file (GoodsData.cpp) is generated at 2018-06-01 16:39:56
*/
#include "GoodsData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include <LocalizationHelper.hpp>

using namespace std;
string GoodsData::getGoodsId() const
{
	return p_goodsId;
}

string GoodsData::getGoodsName() const
{
	string localId = "goods_goodsName_" + p_goodsId;
	return LocalizationHelper::getLocalization(localId);
}

string GoodsData::getType() const
{
	return p_type;
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
	desc += "\tgoodsId : " + p_goodsId+ "\n";
	desc += "\tgoodsName : " + getGoodsName() + "\n";
	desc += "\ttype : " + p_type+ "\n";
	desc += "\ticonId : " + p_iconId+ "\n";
	desc += "\tmaxPrice : " + to_string(p_maxPrice) + "\n";
	desc += "\tlevelUpExp : " + to_string(p_levelUpExp) + "\n";
	desc += "\tgoodsDescription : " + getGoodsDescription() + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, GoodsData*>* GoodsData::getSharedDictionary()
{
	static unordered_map<string, GoodsData*>* sharedDictionary = nullptr;
	if (!sharedDictionary) {
		sharedDictionary = new unordered_map<string, GoodsData*>();
		static string resPath = "res/base/data/goods.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GoodsData* goodsData = new GoodsData();
				goodsData->p_goodsId = buffer->getString();
				goodsData->p_type = buffer->getString();
				goodsData->p_iconId = buffer->getString();
				goodsData->p_maxPrice = buffer->getInt();
				goodsData->p_levelUpExp = buffer->getInt();
				sharedDictionary->insert(pair<string, GoodsData*>(goodsData->p_goodsId, goodsData));
			}
		}
	}
	return sharedDictionary;
}

GoodsData* GoodsData::getGoodsDataById(const string& goodsId)
{
	return GoodsData::getSharedDictionary()->at(goodsId);
}

