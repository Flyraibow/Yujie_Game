#include "StringParser.h"


int ToInt(const std::string & str)
{
    if (str.empty())
        return 0;

    int i = 0;
    for (char c : str) {
        i *= 10;
        if (c >= '0' && c <= '9')
            i += (int)(c - '0');
        else
            return 0;
    }
    return i;
}

bool ParseIntW(const std::wstring & str, int * out)
{
    if (str.empty())
        return false;

    int i = 0;
    for (wchar_t c : str) {
        i *= 10;
        if (c >= '0' && c <= '9')
            i += (int)(c - '0');
        else
            return false;
    }
    *out = i;
    return true;
}

std::string WStringToString(const std::wstring & wstr)
{
    std::string str;
    str.reserve(wstr.size());
    for (wchar_t c : wstr) {
        str.push_back((char)c);
    }
    return str;
}

std::vector<std::wstring> SplitString(const std::wstring & input, wchar_t delim)
{
    std::vector<std::wstring> output;
    std::wstring::const_iterator left, right;
    left = right = input.begin();
    while (right != input.end()) {
        if (*right == delim) {
            output.emplace_back(left, right);
            left = right;
            ++left;
        }
        ++right;
    }
    output.emplace_back(left, right);
    return output;
}
