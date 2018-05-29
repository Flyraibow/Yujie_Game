//
//  GoodsData.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/28/18.
//

#include "GoodsData.hpp"
#include "LocalizationHelper.hpp"
#include "ByteBuffer.hpp"
#include <string>
#include <unordered_map>

USING_NS_CC;
using namespace std;

static const string s_goodsIconIdBase = "res/base/icon/goods/";
static unordered_map<string, GoodsData*>* s_goodsDataInstance = nullptr;

string GoodsData::getGoodsId() const
{
    return s_goodsId;
}

string GoodsData::getGoodsName() const
{
    string goods_name = "goods_goodsName_" + s_goodsId;
    return LocalizationHelper::getLocalization(goods_name);
}

string GoodsData::getGoodsTypeId() const
{
    return s_goodsTypeId;
}

Sprite* GoodsData::getGoodsIcon() const
{
    string path = s_goodsIconIdBase + s_goodsIconId;
    return Sprite::create(path);
}

int GoodsData::getMaxPrice() const
{
    return s_maxGoodsPrice;
}

int GoodsData::getLevelUpExp() const
{
    return s_levelUpExp;
}

string GoodsData::getGoodsDescription() const
{
    string goods_name = "goods_goodsDescription_" + s_goodsId;
    return LocalizationHelper::getLocalization(goods_name);
}

GoodsData* GoodsData::getGoodsDataById(const string &goodsId)
{
    if (!s_goodsDataInstance) {
        GoodsData::init();
    }
    return s_goodsDataInstance->at(goodsId);
}

bool GoodsData::init()
{
    static string resPath = "res/base/data/goods.dat";
    auto data = FileUtils::getInstance()->getDataFromFile(resPath);
    if (!data.isNull())
    {
        auto bytes = data.getBytes();
        auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
        s_goodsDataInstance = new unordered_map<string, GoodsData*>();
        auto count = buffer->getLong();
        for (int i = 0; i < count; ++i) {
            GoodsData* goodData = new GoodsData();
            goodData->s_goodsId = buffer->getString();
            goodData->s_goodsTypeId = buffer->getString();
            goodData->s_goodsIconId = buffer->getString();
            goodData->s_maxGoodsPrice = buffer->getInt();
            goodData->s_levelUpExp = buffer->getInt();
            s_goodsDataInstance->insert(pair<string, GoodsData*>(goodData->getGoodsId(), goodData));
        }
    }
    return true;
}
