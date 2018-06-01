//
//  CPPClass.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "CPPClass.hpp"

using namespace std;

CPPClass::~CPPClass()
{
    for (auto var : p_publicVariables) {
        delete var;
    }
    for (auto var : p_privateVariables) {
        delete var;
    }
    for (auto func : p_privateFunctions) {
        delete func;
    }
    for (auto func : p_publicFunctions) {
        delete func;
    }
    p_publicVariables.clear();
    p_privateVariables.clear();
    p_privateFunctions.clear();
    p_publicFunctions.clear();
}

void CPPClass::addVariable(const string &varName, const string &varType, bool isPrivate)
{
    auto var = new CPPVariable(varName, varType);
    if (isPrivate) {
        p_privateVariables.push_back(var);
    } else {
        p_publicVariables.push_back(var);
    }
}

void CPPClass::addFunction(const CPPFunction* func, bool isPrivate)
{
    CPPFunction* func_copy = new CPPFunction(*func);
    if (isPrivate) {
        p_privateFunctions.push_back(func_copy);
    } else {
        p_publicFunctions.push_back(func_copy);
    }
}

CPPClass::CPPClass(const string &className)
{
    p_className = className;
}

string CPPClass::getClassName() const
{
    return p_className;
}

string CPPClass::getClassHeaderString() const
{
    string statement = "class " + p_className + "\n{\n";
    statement += "private:\n";
    for (auto vars : p_privateVariables) {
        statement += '\t' + vars->getDefineStatement() + ";\n";
    }
    for (auto func : p_privateFunctions) {
        statement += '\t' +  func->getDefinitionString(nullptr) + ";\n";
    }
    statement += "public:\n";
    for (auto vars : p_publicVariables) {
        statement += '\t' +  vars->getDefineStatement() + ";\n";
    }
    for (auto func : p_publicFunctions) {
        statement += '\t' + func->getDefinitionString(nullptr) + ";\n";
    }
    statement += "};\n";
    return statement;
}

string CPPClass::getClassContentString() const
{
    string statement;
    for (auto func : p_privateFunctions) {
        statement += func->getContentString(this) + "\n";
    }
    for (auto func : p_publicFunctions) {
        statement += func->getContentString(this) + "\n";
    }
    return statement;
}
