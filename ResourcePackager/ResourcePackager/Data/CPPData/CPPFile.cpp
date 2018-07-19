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

const static string kUsingNameSpaceStd = "using namespace std;";

CPPFile::CPPFile(const string &fileName)
{
  p_fileName = fileName;
}

void CPPFile::commonInit()
{
  string comment = "This file (" + this->getFileName() + ") is generated";
  this->addComment(comment);
}

void CPPFile::addEnumClasses(const CPPEnumClass *cppEnumClass)
{
  p_cppEnumClasses.push_back(cppEnumClass);
}

void CPPFile::addClass(const CPPClass *cppClass)
{
  p_cppClasses.push_back(cppClass);
}

void CPPFile::addDefineClass(const string& defineClass)
{
  p_defineClasses.push_back(defineClass);
}

void CPPFile::addComment(const string &comment)
{
  p_cppFileComments.push_back(comment);
}

void CPPFile::addHeaders(const string &headers, bool isQuote)
{
  p_includeHeaders.push_back(make_pair(headers, isQuote));
}

void CPPFile::addPreDefinedClass(const string &preDefinedClass)
{
  p_preDefinedClass.push_back(preDefinedClass);
}

void CPPFile::addNameSpace(const string &nameSpace)
{
  p_usingNamespaces.push_back(nameSpace);
}

string CPPFile::getFileName() const
{
  return p_fileName;
}


string CPPFile::getIncludeHeaderString() const
{
  string statement;
  for (auto includeHeader : p_includeHeaders) {
    char foreBracket = includeHeader.second ? '"' : '<';
    char backBracket = includeHeader.second ? '"' : '>';
    statement += "#include ";
    statement += foreBracket + includeHeader.first + backBracket + '\n';
  }
  return statement;
}

string CPPFile::getDefineClassesString() const
{
  string statement;
  for (auto defineClass : p_defineClasses) {
    statement += "class " + defineClass + ";\n";
  }
  return statement;
}

string CPPFile::getPredefinedClassString() const
{
  string statement;
  for (auto preDefinedClass : p_preDefinedClass) {
    statement += "class " + preDefinedClass + ";\n";
  }
  return statement;
}

string CPPFile::getUsingNamespaceString() const
{
  string statement;
  for (auto usingNamespaces : p_usingNamespaces) {
    statement += usingNamespaces + '\n';
  }
  return statement;
}

string CPPFile::getEmptyLine() const
{
  return "\n";
}

CPPFileHeader::CPPFileHeader(const string &fileName) : CPPFile(fileName)
{
  this->commonInit();
}

string CPPFileHeader::getCppFileString() const
{
  string statement = "/*\n";
  for (auto comment : p_cppFileComments) {
    statement += comment + "\n";
  }
  statement += "*/\n";
  // #ifndef fileName_hpp
  statement += "#ifndef " + p_fileName + "_hpp\n";
  // #define fileName_hpp
  statement += "#define " + p_fileName + "_hpp\n";
  statement += this->getIncludeHeaderString();
  statement += this->getEmptyLine();
  statement += this->getDefineClassesString();
  statement += this->getEmptyLine();
  statement += this->getUsingNamespaceString();
  statement += this->getPredefinedClassString();
  
  for (auto cppEnumClass : p_cppEnumClasses) {
    statement += cppEnumClass->getClassContentString();
  }
  
  for (auto cppClass : p_cppClasses) {
    statement += cppClass->getClassHeaderString();
  }
  // #endif
  statement += "#endif\n";
  return statement;
}

string CPPFileHeader::getFileName() const
{
  return p_fileName + ".hpp";
}

CPPFileContent::CPPFileContent(const string &fileName) : CPPFile(fileName)
{
  this->commonInit();
}

string CPPFileContent::getCppFileString() const
{
  string statement = "/*\n";
  for (auto comment : p_cppFileComments) {
    statement += comment + "\n";
  }
  statement += "*/\n";
  statement += this->getIncludeHeaderString();
  statement += this->getEmptyLine();
  statement += this->getDefineClassesString();
  statement += this->getEmptyLine();
  statement += this->getUsingNamespaceString();
  
  for (auto cppEnumClass : p_cppEnumClasses) {
    statement += cppEnumClass->getClassContentString();
  }
  
  for (auto cppClass : p_cppClasses) {
    statement += cppClass->getClassContentString();
  }
  return statement;
}

string CPPFileContent::getFileName() const
{
  return p_fileName + ".cpp";
}


CPPFileComplete::CPPFileComplete(const string &fileName) : CPPFile(fileName)
{
  p_headerFile = new CPPFileHeader(fileName);
  p_contentFile = new CPPFileContent(fileName);
  p_contentFile->addHeaders(p_headerFile->getFileName(), true);
  p_headerFile->addNameSpace(kUsingNameSpaceStd);
  p_contentFile->addNameSpace(kUsingNameSpaceStd);
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

void CPPFileComplete::addPreDefinedClass(const string &preDefinedClass)
{
  p_headerFile->addPreDefinedClass(preDefinedClass);
}

void CPPFileComplete::addEnumClass(const CPPEnumClass *cppEnumClass, bool isHeader)
{
  if (isHeader) {
    p_headerFile->addEnumClasses(cppEnumClass);
  } else {
    p_contentFile->addEnumClasses(cppEnumClass);
  }
}

void CPPFileComplete::addClass(const CPPClass *cppClass)
{
  p_headerFile->addClass(cppClass);
  p_contentFile->addClass(cppClass);
}

void CPPFileComplete::addDefineClass(const string& defineClass, bool isHeader)
{
  if (isHeader) {
    p_headerFile->addDefineClass(defineClass);
  } else {
    p_contentFile->addDefineClass(defineClass);
  }
}

void CPPFileComplete::addHeaders(const string &headers, bool isQuote, bool isHeader)
{
  if (isHeader) {
    p_headerFile->addHeaders(headers, isQuote);
  } else {
    p_contentFile->addHeaders(headers, isQuote);
  }
}

void CPPFileComplete::saveFiles(const string& folderPath)
{
  // write header file
  string headerFileName = p_headerFile->getFileName();
  utils::writeStringToFile(this->getCppFileStringHeader(), folderPath, headerFileName);
  
  // write content file
  string contentFileName = p_contentFile->getFileName();
  utils::writeStringToFile(this->getCppFileStringContent(), folderPath, contentFileName);
}


