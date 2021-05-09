#ifndef CELL_HPP
#define CELL_HPP

#include <string>
#include <stdio.h>
#include "Tile.hpp"

using namespace std;

// Cell score
typedef enum {
    DL = 0, // Double letter
    TL, // Triple letter
    DW, // Double word
    TW, // Triple word
    NO_EFFECT // Nothing
} ScoreEffect;

class Cell {
public:
    Cell() : m_scoreEffect(NO_EFFECT), m_empty(true), m_tilePlayed(false) {}

    void setTile(Tile const tile);
    void deleteTile();
    Tile getTile() const { return m_tile; }
    void setScore(string score);
    void setIsEmpty(bool empty) { m_empty = empty; }
    void setPlayed(bool play) { m_tilePlayed = play; }
    void cleanScore() { m_scoreEffect = NO_EFFECT; }
    ScoreEffect getScore() const { return m_scoreEffect; }
    bool isEmpty() const { return m_empty; }
    bool played() const { return m_tilePlayed; }

private:
    ScoreEffect m_scoreEffect;
    Tile m_tile;
    bool m_empty;
    bool m_tilePlayed;
};

#endif
