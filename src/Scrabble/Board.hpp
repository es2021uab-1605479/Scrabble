#ifndef BOARD_HPP
#define BOARD_HPP

#include <stdio.h>
#include <string>
#include "../Config.hpp"
#include "Cell.hpp"
#include "Dictionary.cpp"
#include "BoardPosition.hpp"

using namespace std;

// (0,0) ----> X
//   |  (col:0, row:0), (col:1, row:0)
//   |  (col:0, row:1), (col:1, row:1)
//   |     <- Size X (width)->
//   |      Coordinate system
//   v
//   Y

typedef enum {
    VALID_POSITION = 0,
    INVALID_POSITION,
    NOT_EMPTY
} PositionResult;

typedef enum {
    ALL_CORRECT = 0,
    // Tiles must be vertically or horizontally aligned and together
    INVALID_NOT_ALIGNED,
    // At least one letter must be next to the rest of the words.
    INVALID_NOT_CONNECTION,
    // You have to start using the center position
    INVALID_START_NOT_IN_CENTER,
    // Only words of two or more letters
    INVALID_WORD_OF_ONE_LETTER,
    // The new words are not in the dictionary
    INVALID_WORDS_NOT_IN_DICTIONARY,
} CurrentWordResult;

class Board {
public:
    Board();
    PositionResult setTile(Tile& tile, const BoardPosition& boardPos);
    CurrentWordResult checkCurrentWord(int& points);
    int trobaAlineacio();
    bool comprovaConsecutiu(int tipusAlineacio, int& min, int& max);
    bool comprovaConnexio(int tipusAlineacio, int min, int max);
    void buscaParaulesNoves(int tipusAlineacio, int min, int max);
    void sendCurrentWordToBoard();
    void removeCurrentWord();
    bool getFirst() { return m_isFirst; }
    int getTotalScore();
    void cleanScore();

private:
    vector<Tile> currentWordTiles;
    int m_wordLength;
    int currentScore;
    bool m_isFirst;
    Cell m_cells[BOARD_COLS_AND_ROWS][BOARD_COLS_AND_ROWS];
    Dictionary m_dictionary;
    vector<char> currentWord;
    vector<string> m_paraules;
    vector<BoardPosition> currentWordPosition;
    vector<Tile> allTilesScore;
    vector<BoardPosition> allBPScore;
};

#endif
