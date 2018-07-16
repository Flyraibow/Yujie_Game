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
  cppFile->addHeaders(friendClassName + ".hpp", true, true);
}
