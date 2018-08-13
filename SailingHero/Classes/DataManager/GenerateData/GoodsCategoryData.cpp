/*
This file (GoodsCategoryData.cpp) is generated
*/
#include "GoodsCategoryData.hpp"
#include "cocos2d.h"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include <LocalizationHelper.hpp>


using namespace SHUtil;

map<int, GoodsCategoryData*>* GoodsCategoryData::p_sharedDictionary = nullptr;

string GoodsCategoryData::getId() const
{
	return to_string(p_categoryId);
}

int GoodsCategoryData::getCategoryId() const
{
	return p_categoryId;
}

string GoodsCategoryData::getCategoryName() const
{
	string localId = "goodsCategory_categoryName_" + to_string(p_categoryId);
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
	desc += "\tcategoryName : " + getCategoryName() + "\n";
	desc += "\tcategoryUpdate : " + to_string(p_categoryUpdateId) + "\n";
	desc += "}\n";
	return desc;
}

const map<int, GoodsCategoryData*>* GoodsCategoryData::getSharedDictionary()
{
	if (!p_sharedDictionary) {
		p_sharedDictionary = new map<int, GoodsCategoryData*>();
		static string resPath = "res/base/data/goodsCategory.dat";
		auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);
		if (!data.isNull()) {
			auto bytes = data.getBytes();
			auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
			auto count = buffer->getLong();
			for (int i = 0; i < count; ++i) {
				GoodsCategoryData* goodsCategoryData = new GoodsCategoryData();
				goodsCategoryData->p_categoryId = buffer->getInt();
				goodsCategoryData->p_categoryUpdateId = buffer->getString();
				p_sharedDictionary->insert(pair<int, GoodsCategoryData*>(goodsCategoryData->p_categoryId, goodsCategoryData));
			}
		}
	}
	return p_sharedDictionary;
}

GoodsCategoryData* GoodsCategoryData::getGoodsCategoryDataById(int categoryId)
{
	if (GoodsCategoryData::getSharedDictionary()->count(categoryId)) {
		return GoodsCategoryData::getSharedDictionary()->at(categoryId);
	}
	return nullptr;
}

GoodsCategoryData* GoodsCategoryData::getGoodsCategoryDataById(const string& categoryId)
{
	if (categoryId.length() == 0) return nullptr;
	return GoodsCategoryData::getGoodsCategoryDataById(atoi(categoryId.c_str()));
}

string GoodsCategoryData::getFieldValue(const string & fieldName)
{
	if (fieldName == "categoryId") {
		return to_string(this->getCategoryId());
	} else if (fieldName == "categoryName") {
		return to_string(this->getCategoryName());
	} else if (fieldName == "categoryUpdate") {
		return to_string(this->getCategoryUpdateId());
	}
	CCLOGWARN("Couldn't recognize %s in GoodsCategoryData", fieldName.c_str());
	return "";
}

