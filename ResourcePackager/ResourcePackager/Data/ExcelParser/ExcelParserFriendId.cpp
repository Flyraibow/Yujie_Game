//
//  ExcelParserFriendId.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserFriendId.hpp"


ExcelParserFriendId::ExcelParserFriendId(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  
}

string ExcelParserFriendId::getVariableName() const
{
  return "p_" + p_schema->getName() + "Id";
}

string ExcelParserFriendId::getVariableGetterName() const
{
  return this->ExcelParserBase::getVariableGetterName() + "Id";
}

string ExcelParserFriendId::getVariableSetterName() const
{
  return this->ExcelParserBase::getVariableSetterName() + "Id";
}

void ExcelParserFriendId::addFunctionsInclass(CPPClass *cppClass) const
{
  string friendClassName = p_schema->getSubtype() + "Data";
  auto getSchemaFuncName = this->ExcelParserBase::getVariableGetterName() + "Data";
  auto getFriendDataFunc = new CPPFunction(getSchemaFuncName, friendClassName + "*");
  getFriendDataFunc->addBodyStatements("return " + friendClassName + "::get" + friendClassName + "ById(" + this->getVariableName() +");");
  cppClass->addFunction(getFriendDataFunc, false);
  this->ExcelParserBase::addFunctionsInclass(cppClass);
}

void ExcelParserFriendId::addHeaders(CPPFileComplete *cppFile) const
{
  string friendClassName = p_schema->getSubtype() + "Data";
  bool defineInHeader = !p_schema->isWeak();
  if (!defineInHeader) {
    cppFile->addDefineClass(friendClassName, true);
  }
  cppFile->addHeaders(friendClassName + ".hpp", true, defineInHeader);
}

void ExcelParserFriendId::addGetFieldDataValueFuncBody(CPPFunction *getFieldFunc) const
{
  getFieldFunc->addBodyStatements("\treturn this->" + ExcelParserBase::getVariableGetterName()+ "Data();");
}
