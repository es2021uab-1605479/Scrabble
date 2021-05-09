#include <string>
#include "Cell.hpp"

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

void Cell::setTile(Tile const tile) {
    m_tile.setLetter(tile.getLetter());
    m_tile.setScore(tile.getScore());
    m_empty = false;
}

void Cell::deleteTile() {
    m_tile.setLetter(' ');
    m_tile.setScore(0);
    m_empty = true;
    m_tilePlayed = false;
}
