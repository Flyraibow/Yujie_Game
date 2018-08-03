#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <vector>

int ToInt(const std::string & str);

bool ParseIntW(const std::wstring & str, int * out);

std::string WStringToString(const std::wstring & wstr);

std::vector<std::wstring> SplitString(const std::wstring & input, wchar_t delim = L',');

#endif