#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <stdio.h>
#include <iostream>

typedef enum {
    CATALAN = 0,
    SPANISH,
    ENGLISH,
    NO_LANGUAGE
} Language;

class Dictionary {
public:
    Dictionary();

    void setLanguage(Language language);
    Language getCurrentLanguage() { return m_currentLanguage; }
    bool check(const string& word);

private:
	vector<string> m_words;
    string m_languagesPath[NO_LANGUAGE];
    Language m_currentLanguage;
};

#endif
