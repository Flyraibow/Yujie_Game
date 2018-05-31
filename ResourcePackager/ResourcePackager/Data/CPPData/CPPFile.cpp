//
//  CPPFile.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "CPPFile.hpp"
#include "TimeUtil.hpp"
#include "Utils.hpp"

using namespace std;


CPPFile::CPPFile(const string &fileName)
{
    p_fileName = fileName;
    auto s = dateTimeToString(now(), "%Y-%m-%d %H:%M:%S");
    string comment = "This file is generated at " + s;
    this->addComment(comment);
}

void CPPFile::addClass(CPPClass *cppClass)
{
    p_cppClasses.push_back(cppClass);
}

void CPPFile::addComment(const string &comment)
{
    p_cppFileComments.push_back(comment);
}

void CPPFile::addHeaders(const string &headers)
{
    p_includeHeaders.push_back(headers);
}


void CPPFile::addNameSpace(const string &nameSpace)
{
    p_usingNamespaces.push_back(nameSpace);
}

CPPFileHeader::CPPFileHeader(const string &fileName) : CPPFile(fileName)
{
}

string CPPFileHeader::getCppFileString() const
{
    string statement = "/*\n";
    for (auto comment : p_cppFileComments) {
        statement += comment + "\n";
    }
    statement += "*/\n";
    return statement;
}

CPPFileContent::CPPFileContent(const string &fileName) : CPPFile(fileName)
{
}

string CPPFileContent::getCppFileString() const
{
    string statement = "/*\n";
    for (auto comment : p_cppFileComments) {
        statement += comment + "\n";
    }
    statement += "*/\n";
    return statement;
}


CPPFileComplete::CPPFileComplete(const string &fileName) : CPPFile(fileName)
{
    p_headerFile = new CPPFileHeader(fileName);
    p_contentFile = new CPPFileContent(fileName);
}

CPPFileComplete::~CPPFileComplete()
{
    delete p_headerFile;
    delete p_contentFile;
}

string CPPFileComplete::getCppFileStringHeader() const
{
    return p_headerFile->getCppFileString();
}

string CPPFileComplete::getCppFileStringContent() const
{
    return p_contentFile->getCppFileString();
}


void CPPFileComplete::saveFiles(const string& folderPath, const string& fileName)
{
    // write header file
    string headerFileName = fileName + ".hpp";
    utils::writeStringToFile(this->getCppFileStringHeader(), folderPath, headerFileName);
    
    // write content file
    string contentFileName = fileName + ".cpp";
    utils::writeStringToFile(this->getCppFileStringHeader(), folderPath, contentFileName);
}

