//
//  ExcelParserFriendIdVector.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserFriendIdVector.hpp"

ExcelParserFriendIdVector::ExcelParserFriendIdVector(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  
}

string ExcelParserFriendIdVector::getVariableName() const
{
  return "p_" + p_schema->getName() + "IdVector";
}

string ExcelParserFriendIdVector::getVariableGetterName() const
{
  return this->ExcelParserBase::getVariableGetterName() + "IdVector";
}

void ExcelParserFriendIdVector::addFunctionsInclass(CPPClass *cppClass) const
{
  string friendClassName = p_schema->getSubtype() + "Data";
  string friendClassSetName = "vector<" +friendClassName + "*>";
  auto getSchemaFuncName = this->ExcelParserBase::getVariableGetterName() + "DataVector";
  auto getFriendDataFunc = new CPPFunction(getSchemaFuncName, friendClassSetName);
  getFriendDataFunc->addBodyStatementsList({
    friendClassSetName + " resultVector;",
    "for (auto objId : " + this->getVariableName() + ") {",
    "\tresultVector.push_back(" + friendClassName + "::get" + friendClassName + "ById(objId));",
    "}",
    "return resultVector;"
  }, 0);
  cppClass->addFunction(getFriendDataFunc, false);
  this->ExcelParserBase::addFunctionsInclass(cppClass);
}

void ExcelParserFriendIdVector::addHeaders(CPPFileComplete *cppFile) const
{
  string friendClassName = p_schema->getSubtype() + "Data";
  cppFile->addHeaders(friendClassName + ".hpp", true, true);
}
