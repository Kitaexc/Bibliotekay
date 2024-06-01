#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

int main() {
    setlocale(0, "");
    string inputStr;
    string inputChars;

    cout << "Строчечьку на базу: ";
    getline(cin, inputStr);

    cout << "Кого искать будем: ";
    getline(cin, inputChars);

    HINSTANCE hLib = LoadLibrary(L"liba.dll");
    if (hLib == NULL) {
        cerr << "Библиотеки больше нет!" << endl;
        return 1;
    }

    ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib, "contains_all_chars");
    if (contains_all_chars == NULL) {
        cerr << "Не удалось получить адрес функции!" << endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

    cout << (result ? "Дасишь фантастишь" : "Не дасишь фантастишь") << endl;

    FreeLibrary(hLib);

    return 0;
}