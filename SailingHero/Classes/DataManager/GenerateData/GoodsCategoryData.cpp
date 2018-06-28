/*
This file (GoodsCategoryData.cpp) is generated at 2018-06-27 22:21:10
*/
#include "GoodsCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>

using namespace std;
string GoodsCategoryData::getCategoryId() const
{
	return p_categoryId;
}

string GoodsCategoryData::getCategory_name() const
{
	string localId = "goodsCategory_category_name_" + p_categoryId;
	return LocalizationHelper::getLocalization(localId);
}

CategoryUpdateData* GoodsCategoryData::getCategoryUpdateData() const
{
	return CategoryUpdateData::getCategoryUpdateDataById(p_categoryUpdateId);
}

string GoodsCategoryData::getCategoryUpdateId() const
{
	return p_categoryUpdateId;
}

string GoodsCategoryData::description() const
{
	string desc = "goodsCategoryData = {\n";
	desc += "\tcategoryId : " + to_string(p_categoryId) + "\n";
	desc += "\tcategory_name : " + getCategory_name() + "\n";
	desc += "\tcategoryUpdateId : " + to_string(p_categoryUpdateId) + "\n";
	desc += "}\n";
	return desc;
}

unordered_map<string, GoodsCategoryData*>* GoodsCategoryData::getSharedDictionary()
{
	static unordered_map<string, GoodsCategoryData*>* sharedDictionary = nullptr;
	if (!sharedDictionary) {
		sharedDictionary = new unordered_map<string, GoodsCategoryData*>();
		static string resPath = "res/base/data/goodsCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GoodsCategoryData* goodsCategoryData = new GoodsCategoryData();
				goodsCategoryData->p_categoryId = buffer->getString();
				goodsCategoryData->p_categoryUpdateId = buffer->getString();
				sharedDictionary->insert(pair<string, GoodsCategoryData*>(goodsCategoryData->p_categoryId, goodsCategoryData));
			}
		}
	}
	return sharedDictionary;
}

GoodsCategoryData* GoodsCategoryData::getGoodsCategoryDataById(const string& categoryId)
{
	if (GoodsCategoryData::getSharedDictionary()->count(categoryId)) {
		return GoodsCategoryData::getSharedDictionary()->at(categoryId);
	}
	CCLOGERROR("invalid categoryId %s", categoryId.c_str());
	return nullptr;
}

