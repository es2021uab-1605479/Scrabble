#include <algorithm>
#include <iostream>
#include <fstream>
#include "../Config.hpp"
#include "Board.hpp"
#include "Cell.cpp"

Board::Board() {
	int col, fila;
	string score;
	ifstream fitxer;

	fitxer.open(DATA_DIRECTORY + "/Configuration/board.txt");

	if (fitxer.is_open()) {
		while (!fitxer.eof()) {
			fitxer >> col >> fila >> score;
			m_cells[col][fila].setScore(score);
		}
		fitxer.close();
    } else {
        cout << "(i) FAILED TO READ CONFIGURATION" << endl;
    }

	m_wordLength = 0;
	m_isFirst = true;
}

// Calcula si l'alineació de la paraula actual és horitzontal o vertical
// Retorna 1 si és horitzontal, 2 si vertical, 0 si no se sap
int Board::trobaAlineacio() {
    int row = currentWordPosition[0].getRow();
    int col = currentWordPosition[0].getCol();
    bool vertical = true;
    bool horitzontal = true;

	int i = 0, j = 0;

	while (i < currentWord.size() && horitzontal) {
		if (currentWordPosition[i].getRow() != row) 
			horitzontal = false;
		i++;
	}

	while (j < currentWord.size() && vertical) {
		if (currentWordPosition[j].getCol() != col)
			vertical = false;
		j++;
	}

	if (horitzontal)
		return 1;
	else if (vertical)
		return 2;

    return 0;
}

// Check if letters are consecutive given the alignment type
bool Board::comprovaConsecutiu(int tipusAlineacio, int& min, int& max) {
    bool consecutiu = true;
    int col, row;
	int j;

	switch (tipusAlineacio) {
		case 1:
            // alineació horitzontal
			row = currentWordPosition[0].getRow();
			min = currentWordPosition[0].getCol();
			max = currentWordPosition[0].getCol();

            if (currentWord.size() == 1)
                break;

			for (int i = 1; i < currentWord.size(); i++) {
				if (currentWordPosition[i].getCol() < min)
					min = currentWordPosition[i].getCol();
				if (currentWordPosition[i].getCol() > max)
					max = currentWordPosition[i].getCol();
			}

			j = min;

			while (j < max && consecutiu) {
				if (m_cells[j][row].isEmpty()){
                    consecutiu = false;
				}

                j++;
			}

			break;

		case 2:
            // alineació vertical
            col = currentWordPosition[0].getCol();
            min = currentWordPosition[0].getRow();
            max = min;

            if (currentWord.size() == 1)
                break;

            for (int i = 1; i < currentWord.size(); i++) {
                if (currentWordPosition[i].getRow() < min)
                    min = currentWordPosition[i].getRow();
                if (currentWordPosition[i].getRow() > max)
                    max = currentWordPosition[i].getRow();
            }

            j = min;

            while (j < max && consecutiu) {
                if (m_cells[col][j].isEmpty()){
                    consecutiu = false;
                }

                j++;
            }

            break;

		default:
			break;
	}

	return consecutiu;
}

// Check if word is connected to previous words given the alignment type
bool Board::comprovaConnexio(int tipusAlineacio, int min, int max) {
    bool connexio = false;

    switch (tipusAlineacio) {
        case 1:
            // alineació horitzontal
            for (int i = 0; i < currentWord.size(); i++) {
                if (currentWordPosition[i].getCol() == min) {
                    if (!m_cells[min - 1][currentWordPosition[i].getRow()].isEmpty())
                        connexio = true;
                } else if (currentWordPosition[i].getCol() == max) {
                    if (!m_cells[max + 1][currentWordPosition[i].getRow()].isEmpty())
                        connexio = true;
                }
                if (!m_cells[min + i][currentWordPosition[i].getRow() - 1].isEmpty())
                    connexio = true;
                if (!m_cells[min + i][currentWordPosition[i].getRow() + 1].isEmpty())
                    connexio = true;
            }

            break;

        case 2:
            // alineació vertical
            for (int i = 0; i < currentWord.size(); i++) {
                if (currentWordPosition[i].getRow() == min) {
                    if (!m_cells[currentWordPosition[i].getCol()][min - 1].isEmpty())
                        connexio = true;
                } else if (currentWordPosition[i].getRow() == max) {
                    if (!m_cells[currentWordPosition[i].getCol()][max + 1].isEmpty())
                        connexio = true;
                }

                if (!m_cells[currentWordPosition[i].getCol() - 1][min + i].isEmpty())
                    connexio = true;

                if (!m_cells[currentWordPosition[i].getCol() + 1][min + i].isEmpty())
                    connexio = true;
            }

            break;

        default:
            break;
    }

    return connexio;
}

// Add a tile to the board during player's turn
PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos) {
    if (boardPos.getCol() >= 0 && boardPos.getRow() >= 0) {
        if (boardPos.getCol() < 15 && boardPos.getRow() < 15) {
            // Check if tile has already been occupied during previous rounds
            if (m_cells[boardPos.getCol()][boardPos.getRow()].isEmpty()) {
                // Check if tile has already been occupied during this round
                for (unsigned int i = 0; i < currentWordPosition.size(); i++) {
                    if (currentWordPosition[i] == boardPos) {
                        return NOT_EMPTY;
                    }
                }

                // Set the tile on the board
                m_cells[boardPos.getCol()][boardPos.getRow()].setTile(tile);

                // Add it to currentWord and increase character count
                currentWord.push_back(tile.getLetter());
                currentWordPosition.push_back(boardPos);
                currentWordTiles.push_back(tile);
                m_wordLength++;

                return VALID_POSITION;
            } else {
                return NOT_EMPTY;
            }
        }
    }
    return INVALID_POSITION;
}

// Find new words from inserted tiles
void Board::buscaParaulesNoves(int tipusAlineacio, int min, int max) {
    BoardPosition posScore;
    int j, cont = 0;
    bool edge = false;
    string paraula = "";

    switch (tipusAlineacio) {
        case 1:
            j = currentWordPosition[0].getRow();

            while (!m_cells[min - cont][j].isEmpty()) {
                cont++;
            }

            while ((!m_cells[min - cont + 1][j].isEmpty() || m_cells[min - cont + 1][j].played()) && ((min - cont + 1) < 15)) {
                paraula += m_cells[min - cont + 1][j].getTile().getLetter();
                allTilesScore.push_back(m_cells[min - cont + 1][j].getTile());
                posScore.setCol(min - cont + 1);
                posScore.setRow(j);
                allBPScore.push_back(posScore);
                cont--;
            }

            if (paraula != "") {
                m_paraules.push_back(paraula);
                paraula = "";
            }

            for (int i = 0; i < currentWordPosition.size(); i++) {
                if (!m_cells[min + i][j - 1].isEmpty() && !m_cells[min + i][j].played()) {
                    while (!m_cells[min + i][j].isEmpty() && !edge) { //Buscar posInicial
                        if (j == 0)
                            edge = true;
                        else
                            j--;
                    }

                    while (!m_cells[min + i][j + 1].isEmpty() && !edge) { //Buscar posFinal i anar afegint paraules
                        if (j == 15)
                            edge = true;
                        paraula += m_cells[min + i][j + 1].getTile().getLetter();
                        allTilesScore.push_back(m_cells[min + i][j + 1].getTile());
                        posScore.setCol(min + i);
                        posScore.setRow(j + 1);
                        allBPScore.push_back(posScore);
                        j++;
                    }

                    if (paraula != "") {
                        m_paraules.push_back(paraula);
                        paraula = "";
                    }
                }
            }

            break;

        case 2:
            j = currentWordPosition[0].getCol();

            while (!m_cells[j][min - cont].isEmpty()) {
                cont++;
            }

            while ((!m_cells[j][min - cont + 1].isEmpty() || m_cells[j][min - cont + 1].played()) && ((min - cont + 1) < 15)) {
                paraula += m_cells[j][min - cont + 1].getTile().getLetter();
                allTilesScore.push_back(m_cells[j][min - cont + 1].getTile());
                posScore.setCol(j);
                posScore.setRow(min - cont + 1);
                allBPScore.push_back(posScore);
                cont--;
            }

            if (paraula != "") {
                m_paraules.push_back(paraula);
                paraula = "";
            }
            
            for (int i = 0; i < currentWordPosition.size(); i++) {
                if (!m_cells[j][min + i].played())
                if (!m_cells[j - 1][min + i].isEmpty() || m_cells[j - 1][min + i].played()) {
                    while (!m_cells[j][min + i].isEmpty() && !edge) {
                        //Buscar posInicial
                        if (j == 0)
                            edge = true;
                        else
                            j--;
                    }

                    while (!m_cells[j + 1][min + i].isEmpty() && !edge) { //Buscar posFinal i anar afegint paraules
                        if (j == 15)
                            edge = true;

                        paraula += m_cells[j + 1][min + i].getTile().getLetter();
                        allTilesScore.push_back(m_cells[j + 1][min + i].getTile());
                        posScore.setCol(j + 1);
                        posScore.setRow(min + i);
                        allBPScore.push_back(posScore);
                        j++;
                    }

                    if (paraula != "") {
                        m_paraules.push_back(paraula);
                        paraula = "";
                    }
                }
            }

            break;

        default:
            break;
    }
}

// Check if current inserted word is consecuive and connected
CurrentWordResult Board::checkCurrentWord(int& points) {
    int min, max;

    int tipusAlineacio = trobaAlineacio();
    bool consecutiu = comprovaConsecutiu(tipusAlineacio, min, max);
    bool connectat = comprovaConnexio(tipusAlineacio, min, max);

    buscaParaulesNoves(tipusAlineacio, min, max);

    if (getFirst()) {
        BoardPosition inicial(7, 7);
        bool correcte = false;
        unsigned int j = 0;

        while (!correcte && j < currentWordPosition.size()) {
            if (currentWordPosition[j] == inicial) {
                correcte = true;
            } else {
                j++;
            }
        }

        if (correcte && consecutiu) {
            if (m_wordLength < 2) {
                return INVALID_WORD_OF_ONE_LETTER;
            } else if (!m_dictionary.check(m_paraules[0])) {
                return INVALID_WORDS_NOT_IN_DICTIONARY;
            } else {
                m_isFirst = false;
                points = getTotalScore();
                return ALL_CORRECT;
            }
        } else {
            return INVALID_START_NOT_IN_CENTER;
        }
    } else {
        int wordScore;
        bool dobleWord = false, tripleWord = false;

        for (int i = 0; i < m_paraules.size(); i++) {
            if (m_wordLength < 2) {
                return INVALID_WORD_OF_ONE_LETTER;
            } else if (!m_dictionary.check(m_paraules[i])) {
                return INVALID_WORDS_NOT_IN_DICTIONARY;
            } else if (!consecutiu) {
                return INVALID_NOT_ALIGNED;
            } else if (!connectat) {
                return INVALID_NOT_CONNECTION;
            } else if (connectat && consecutiu) {
                for (unsigned int i = 0; i < m_paraules.size(); i++) {
                    wordScore = 0;
                    dobleWord = false;
                    tripleWord = false;

                    for (unsigned int j = 0; j < m_paraules[i].length(); j++) {
                        if (m_cells[allBPScore[i + j].getCol()][allBPScore[i + j].getRow()].getScore() == DL) {
                            wordScore += allTilesScore[i + j].getScore() * 2;
                        } else if (m_cells[allBPScore[i + j].getCol()][allBPScore[i + j].getRow()].getScore() == TL) {
                            wordScore += allTilesScore[i + j].getScore() * 3;
                        } else if (m_cells[allBPScore[i + j].getCol()][allBPScore[i + j].getRow()].getScore() == DW) {
                            wordScore += allTilesScore[i + j].getScore();
                            dobleWord = true;
                        } else if (m_cells[allBPScore[i + j].getCol()][allBPScore[i + j].getRow()].getScore() == TW) {
                            wordScore += allTilesScore[i + j].getScore();
                            tripleWord = true;
                        } else {
                            wordScore += allTilesScore[i + j].getScore();
                        }
                    }
                    
                    if (dobleWord) {
                        wordScore *= 2;
                    }

                    if (tripleWord) {
                        wordScore *= 3;
                    }
                    currentScore += wordScore;
                }

                cleanScore();
                points = currentScore;

                return ALL_CORRECT;
            }
        }

        return INVALID_WORDS_NOT_IN_DICTIONARY;
    }
}

// Clean score for each cell
void Board::cleanScore() {
    for (int i = 0; i < allBPScore.size(); i++) {
        m_cells[allBPScore[i].getCol()][allBPScore[i].getRow()].cleanScore();
    }
}

// Calculate total score on board
int Board::getTotalScore() {
    currentScore = 0;
    bool dobleWord = false;
    bool tripleWord = false;

    for (int i = 0; i < m_wordLength; i++) {
        if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == DL) {
            currentScore += currentWordTiles[i].getScore() * 2;
            m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].cleanScore();
        } else if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == TL) {
            currentScore += currentWordTiles[i].getScore() * 3;
            m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].cleanScore();

        } else if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == DW) {
            currentScore += currentWordTiles[i].getScore();
            dobleWord = true;
            m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].cleanScore();

        } else if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == TW) {
            currentScore += currentWordTiles[i].getScore();
            tripleWord = true;
            m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].cleanScore();

        } else {
            currentScore += currentWordTiles[i].getScore();
        }
    }

    if (dobleWord) {
        currentScore *= 2;
    }

    if (tripleWord) {
        currentScore *= 3;
    }

    return currentScore;
}

// Submit word
void Board::sendCurrentWordToBoard() {
    for (int i = 0; i < m_wordLength; i++) {
        m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].setPlayed(true);
    }

    unsigned long i = m_paraules.size();
    while (i > 0) {
        m_paraules.pop_back();
        i--;
    }

    unsigned long j = currentWord.size();
    while (j > 0) {
        currentWordPosition.pop_back();
        currentWordTiles.pop_back();
        currentWord.pop_back();
        j--;
    }

    unsigned long y = allTilesScore.size();
    while (y > 0) {
        allTilesScore.pop_back();
        allBPScore.pop_back();
        y--;
    }

    currentScore = 0;
    m_wordLength = 0;
}

// Delete all tiles player has placed during current round
void Board::removeCurrentWord() {
    // Empty the tiles
    for (unsigned int i = 0; i < currentWordPosition.size(); i++) {
        m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].deleteTile();
    }

    // Clear the word vectors
    currentWordPosition.clear();
    currentWordTiles.clear();
    currentWord.clear();

    m_wordLength = 0;
}
