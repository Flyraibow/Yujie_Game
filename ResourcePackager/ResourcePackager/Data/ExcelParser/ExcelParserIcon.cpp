//
//  ExcelParserIcon.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserIcon.hpp"

ExcelParserIcon::ExcelParserIcon(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  
}

void ExcelParserIcon::addFunctionsInclass(CPPClass *cppClass) const
{
  string getIconFuncName = this->getVariableGetterName(); // getGoodsIconId
  getIconFuncName = getIconFuncName.substr(0, getIconFuncName.length() - 2);  // getGoodsIcon
  auto varIsDefault = new CPPVariable("isDefaultSize", TYPE_BOOL);
  varIsDefault->setInitialValue("true");
  auto getIconFunction = new CPPFunction(getIconFuncName, "cocos2d::Sprite*", {varIsDefault}, false, false);
  getIconFunction->addBodyStatementsList({
    "static const string s_basePath = \"" + p_schema->getSubtype() + "\";",
    "string path = s_basePath + " + this->getVariableName() + ";",
    "auto icon = cocos2d::Sprite::create(path);",
    "if (!isDefaultSize) {",
    "\ticon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());", "}",
    "return icon;"
    
  }, 0);
  cppClass->addFunction(getIconFunction, false);
  
  string getIconPathFuncName = getIconFuncName + "Path";  // getGoodsIconPath
  auto getIconPathFunction = new CPPFunction(getIconPathFuncName, "string", {}, false, false);
  getIconPathFunction->addBodyStatementsList({
    "static const string s_basePath = \"" + p_schema->getSubtype() + "\";",
    "return s_basePath + " + this->getVariableName() + ";",
  }, 0);
  cppClass->addFunction(getIconPathFunction, false);
  this->ExcelParserBase::addFunctionsInclass(cppClass);
}


void ExcelParserIcon::addGetFieldValueFuncBody(CPPFunction *getFieldFunc) const
{
  ExcelParserBase::addGetFieldValueFuncBody(getFieldFunc);
  string getIconFuncName = this->getVariableGetterName(); // getGoodsIconId
  getIconFuncName = getIconFuncName.substr(0, getIconFuncName.length() - 2) + "Path";  // getGoodsIcon
  getFieldFunc->addBodyStatements("} else if (fieldName == \"" + getIconFuncName + "\") {");
  getFieldFunc->addBodyStatements("\treturn to_string(this->" + getIconFuncName + "());");
}

