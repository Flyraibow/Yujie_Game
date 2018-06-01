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
    vector<CPPClass *> p_cppClasses;
    vector<string> p_cppFileComments;
    vector<string> p_includeHeaders;
    vector<string> p_usingNamespaces;
    void commonInit();
public:
    CPPFile(const string &fileName);
    void addClass(CPPClass *cppClass);
    void addComment(const string &comment);
    void addHeaders(const string &header);
    void addNameSpace(const string &nameSpace);
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

class CPPFileComplete : CPPFile
{
private:
    CPPFileHeader *p_headerFile;
    CPPFileContent *p_contentFile;
public:
    CPPFileComplete(const string &fileName);
    ~CPPFileComplete();
    string getCppFileStringHeader() const;
    string getCppFileStringContent() const;
    void saveFiles(const string& folderPath);
};

#endif /* CPPFile_hpp */
