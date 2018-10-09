//
//  CPPFunction.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "CPPFunction.hpp"
#include "CPPClass.hpp"

CPPFunction::~CPPFunction()
{
  delete p_returnVar;
  flag = 0;
}


CPPFunction::CPPFunction(const CPPFunction &func)
{
  p_isConst = func.p_isConst;
  p_isStatic = func.p_isStatic;
  p_funcName = func.p_funcName;
  p_returnVar = func.p_returnVar;
  p_statements = func.p_statements;
  p_arguments = func.p_arguments;
  flag = 0;
}

CPPFunction::CPPFunction(const string &funcName, const string &returnType) : CPPFunction::CPPFunction(funcName, returnType, {}, false, true)
{
  
}

CPPFunction::CPPFunction(const string &funcName, const string &returnType, bool isStatic) : CPPFunction::CPPFunction(funcName, returnType, {}, isStatic, false)
{
  
}

CPPFunction::CPPFunction(const string &funcName, const string &returnType,const vector<const CPPVariable *> &arguments, bool isStatic, bool isConst, bool isVirtual)
{
  p_funcName = funcName;
  p_isStatic = isStatic;
  p_isConst = isConst;
  p_isVirtual = isVirtual;
  p_returnVar = new CPPVariable(returnType);
  p_arguments = arguments;
}

void CPPFunction::addBodyStatements(const string &statement)
{
  this->addBodyStatements(statement, 0);
}

void CPPFunction::addBodyStatements(const string &statement, int tabNumber)
{
  p_statements.push_back(make_pair(statement, tabNumber));
}


void CPPFunction::addBodyStatementsList(const vector<pair<string, int>> &statementList)
{
  p_statements.insert(p_statements.end(), statementList.begin(), statementList.end());
}

void CPPFunction::addBodyStatementsList(const vector<string> &statementList, int tabNumber)
{
  for (string statement : statementList) {
    this->addBodyStatements(statement, tabNumber);
  }
}

string CPPFunction::getDefinitionString(const CPPClass *cppClass, bool isHeader) const
{
  string definition;
  if (cppClass == nullptr) {
    if (p_isStatic) {
      definition += "static ";
    }
    if (p_isVirtual) {
      definition += "virtual ";
    }
  }
  if (p_returnVar != nullptr) {
    definition += p_returnVar->getTypeString() + " ";
  }
  if (cppClass != nullptr) {
    definition += cppClass->getClassName() + "::";
  }
  definition += p_funcName + "(";
  for (int i = 0; i < p_arguments.size(); ++i) {
    if (i > 0) {
      definition += ", ";
    }
    auto var = p_arguments[i];
    definition += var->getDefineStatement();
    if (isHeader && var->getInitialValue().length() > 0) {
      definition += " = " + var->getInitialValue();
    }
  }
  definition += ")";
  if (p_isConst) {
    definition += " const";
  }
  return definition;
}


string CPPFunction::getContentString(const CPPClass *cppClass) const
{
  string definition = this->getDefinitionString(cppClass, false);
  definition += "\n{\n" + this->getBodyContent() + "}\n";
  
  return definition;
}

string CPPFunction::getReturnTypeString() const
{
  if (p_returnVar != nullptr) {
    return p_returnVar->getTypeString();
  }
  return "";
}

string CPPFunction::getBodyContent() const
{
  string body;
  for (auto statement : p_statements) {
    int tabNumber = statement.second;
    body += string(tabNumber + 1, '\t') + statement.first + '\n';
  }
  return body;
}

