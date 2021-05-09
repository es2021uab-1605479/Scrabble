//
//  Cell.cpp
//  Scrabble
//

#include <string>
#include "./Cell.h"

using namespace std;

void Cell::setScore(string score) {
	if (score == "DL")
		m_scoreEffect = DL;
	else if (score == "TL")
		m_scoreEffect = TL;
	else if (score == "DW")
		m_scoreEffect = DW;
	else if (score == "TW")
		m_scoreEffect = TW;
	else
		m_scoreEffect = NO_EFFECT;
	m_empty = true;
	m_tilePlayed = false;
}


