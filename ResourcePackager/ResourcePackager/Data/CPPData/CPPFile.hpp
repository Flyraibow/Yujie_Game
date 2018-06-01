//
//  CPPFile.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef CPPFile_hpp
#define CPPFile_hpp

#include <stdio.h>
#include "CPPClass.hpp"
#include "CPPFunction.hpp"

#include <vector>
#include <string>

using namespace std;

class CPPFile
{
protected:
    string p_fileName;
    vector<const CPPClass *> p_cppClasses;
    vector<string> p_cppFileComments;
    vector<pair<string, bool>> p_includeHeaders;
    vector<string> p_usingNamespaces;
    vector<string> p_preDefinedClass;
    void commonInit();
    string getIncludeHeaderString() const;
    string getUsingNamespaceString() const;
    string getPredefinedClassString() const;
    string getEmptyLine() const;
public:
    CPPFile(const string &fileName);
    void addClass(const CPPClass *cppClass);
    void addComment(const string &comment);
    void addHeaders(const string &header, bool isQuote);
    void addNameSpace(const string &nameSpace);
    void addPreDefinedClass(const string &preDefinedClass);
    string getCppFileString() const;
    virtual string getFileName() const;
};

class CPPFileHeader : public CPPFile
{
public:
    CPPFileHeader(const string &fileName);
    string getCppFileString() const;
    virtual string getFileName() const;
};

class CPPFileContent : public CPPFile
{
public:
    CPPFileContent(const string &fileName);
    string getCppFileString() const;
    virtual string getFileName() const;
};

class CPPFileComplete : public CPPFile
{
private:
    CPPFileHeader *p_headerFile;
    CPPFileContent *p_contentFile;
public:
    CPPFileComplete(const string &fileName);
    ~CPPFileComplete();
    void addPreDefinedClass(const string &preDefinedClass);
    void addClass(const CPPClass *cppClass);
    void addHeaders(const string &headers, bool isQuote, bool isHeader);
    string getCppFileStringHeader() const;
    string getCppFileStringContent() const;
    void saveFiles(const string& folderPath);
};

#endif /* CPPFile_hpp */
