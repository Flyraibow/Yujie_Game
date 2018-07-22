#include <iostream>

#include "CSVReader.h"

bool ParseInt(const std::wstring & str, int * out)
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

int main() {
    std::cout << "hello" << std::endl;
    CSVReader reader(L"C:\\Users\\celsi\\Desktop\\Projects\\SailingHero\\SailingHero\\plot.csv");
    for (auto line : reader) {
        for (auto token : line) {
            std::wcout << token;
            int i;
            if (ParseInt(token, &i)) {
                std::wcout << "(INT:" << i << ")";
            }
            std::wcout << '\t';
        }
        std::wcout << std::endl;
    }
    return 0;
}
