//
//  Dictionary.cpp


#include "./Dictionary.h"

#include <fstream>
#include <string>

using namespace std;

Dictionary::Dictionary() {
	m_languagesPath[0] = "/src/data/Dictionaries/Catalan.dic";
	m_languagesPath[1] = "/src/data/Dictionaries/Spanish.dic";
	m_languagesPath[2] = "/src/data/Dictionaries/English.dic";

	setLanguage(ENGLISH);
}

void Dictionary::setLanguage(Language l) {
	m_currentLanguage = l;
	string word;
	ifstream fitxer;

	fitxer.open(m_languagesPath[m_currentLanguage]);

	if (fitxer.is_open()) {
		while (!fitxer.eof()) {
			fitxer >> word;
			m_words.push_back(word);
		}
	}
	else {
		cout << "(i) FAILED TO READ DICTIONARY" << endl;
	}

	fitxer.close();
}

bool Dictionary::check(const string& word) {
    bool trobat = false;
    unsigned int i = 0;

    while (!trobat && i < m_words.size()) {
        if (m_words[i] == word) {
            trobat = true;
        }
        i++;
    }

    return trobat;
}