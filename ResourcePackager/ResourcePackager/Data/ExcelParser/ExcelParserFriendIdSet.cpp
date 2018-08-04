//
//  ExcelParserFriendIdSet.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserFriendIdSet.hpp"

ExcelParserFriendIdSet::ExcelParserFriendIdSet(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  
}

string ExcelParserFriendIdSet::getVariableName() const
{
  return "p_" + p_schema->getName() + "IdSet";
}

string ExcelParserFriendIdSet::getVariableGetterName() const
{
  return this->ExcelParserBase::getVariableGetterName() + "IdSet";
}

string ExcelParserFriendIdSet::getVariableSetterName() const
{
  return this->ExcelParserBase::getVariableSetterName() + "IdSet";
}

void ExcelParserFriendIdSet::addFunctionsInclass(CPPClass *cppClass) const
{
  string friendClassName = p_schema->getSubtype() + "Data";
  string friendClassSetName = "set<" +friendClassName + "*>";
  auto getSchemaFuncName = this->ExcelParserBase::getVariableGetterName() + "DataSet";
  auto getFriendDataFunc = new CPPFunction(getSchemaFuncName, friendClassSetName);
  getFriendDataFunc->addBodyStatementsList({
    friendClassSetName + " resultSet;",
    "for (auto objId : " + this->getVariableName() + ") {",
    "\tresultSet.insert(" + friendClassName + "::get" + friendClassName + "ById(objId));",
    "}",
    "return resultSet;"
  }, 0);
  cppClass->addFunction(getFriendDataFunc, false);
  this->ExcelParserBase::addFunctionsInclass(cppClass);
}

void ExcelParserFriendIdSet::addHeaders(CPPFileComplete *cppFile) const
{
  string friendClassName = p_schema->getSubtype() + "Data";
  bool defineInHeader = !p_schema->isWeak();
  if (!defineInHeader) {
    cppFile->addDefineClass(friendClassName, true);
  }
  cppFile->addHeaders(friendClassName + ".hpp", true, defineInHeader);
}

string ExcelParserFriendIdSet::getType() const
{
  assert(p_schema->getType() == FRIEND_ID_SET);
  return TYPE_SET(TYPE_STRING);
}

void ExcelParserFriendIdSet::addInitFuncBody(CPPFunction *func, const string &variableName, int level) const
{
  string schemaName = this->getVariableName();
  func->addBodyStatementsList({
    "auto " + p_schema->getName() + "Count = buffer->getLong();",
    "for (int j = 0; j < " + p_schema->getName() + "Count; ++j) {",
    "\t" + variableName + "->" + schemaName + ".insert(buffer->getString());",
    "}"
  }, level);
}
