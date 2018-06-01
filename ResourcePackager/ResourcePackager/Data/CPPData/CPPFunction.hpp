//
//  CPPFunction.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef CPPFunction_hpp
#define CPPFunction_hpp

#include <stdio.h>
#include "CPPVariable.hpp"
#include <vector>

using namespace std;

class CPPClass;

class CPPFunction
{
private:
    bool p_isConst;
    bool p_isStatic;
    string p_funcName;
    vector<const CPPVariable *> p_arguments;
    const CPPVariable *p_returnVar;
    vector<pair<string, int>> p_statements;
public:
    ~CPPFunction();
    CPPFunction(const CPPFunction &func);
    CPPFunction(const string &funcName, const string &returnType);
    CPPFunction(const string &funcName, const string &returnType, bool isStatic);
    CPPFunction(const string &funcName, const string &returnType, const vector<const CPPVariable *> &arguments, bool isStatic, bool isConst);
    void addBodyStatements(const string &statement);
    void addBodyStatements(const string &statement, int tabNumber);
    void addBodyStatementsList(const vector<pair<string, int>> &statementList);
    void addBodyStatementsList(const vector<string> &statementList, int tabNumber);
    string getDefinitionString(const CPPClass *cppClass) const;
    string getContentString(const CPPClass *cppClass) const;
    string getReturnTypeString() const;
    string getBodyContent() const;
};

#endif /* CPPFunction_hpp */
