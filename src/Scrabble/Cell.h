//
//  Cell.hpp
//  Scrabble
//


#ifndef Cell_hpp
#define Cell_hpp

#include <string>
#include <stdio.h>
#include "./Tile.h"

using namespace std;

typedef enum {
    DL = 0,
    TL,
    DW,
    TW,
    NO_EFFECT
} ScoreEffect;

class Cell
{
public:
	Cell() { m_scoreEffect = NO_EFFECT, m_empty = true, m_tilePlayed = false; }
	~Cell() {}
	void setTile(Tile const tile) {
		m_tile = tile;
		m_empty = false;
	}
	Tile getTile() const { return m_tile; }
	void setScore(string score);
	void setIsEmpty(bool empty) { m_empty = empty; }
	ScoreEffect getScore() const { return m_scoreEffect; }
	bool isEmpty() const { return m_empty; }
private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};


#endif /* Cell_hpp */
