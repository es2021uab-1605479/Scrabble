
//  Board.cpp
//  Scrabble
//

#include "./Board.h"
#include <algorithm>
#include <iostream>
#include <fstream>



Board::Board() {
	int col, fila;
	string score;
	ifstream fitxer;

	fitxer.open("data/Configuration/board.txt");

	if (fitxer.is_open()) {
		while (!fitxer.eof()) {
			fitxer >> col >> fila >> score;
			m_cells[col][fila].setScore(score);
		}
		fitxer.close();
	}
	m_wordLength = 0;
	m_dictionary.setLanguage(ENGLISH);
	m_isFirst = true;
}

PositionResult Board::setTile(Tile& tile, const BoardPosition& boardPos) {
	if (boardPos.getCol() >= 0 && boardPos.getRow() >= 0) {
		if (boardPos.getCol() < 15 && boardPos.getRow() < 15) {
			if (m_cells[boardPos.getCol()][boardPos.getRow()].isEmpty()) {
				for (unsigned int i = 0; i < currentWordPosition.size(); i++) {
					if (currentWordPosition[i] == boardPos) {
						return NOT_EMPTY;
					}
				}
				//m_cells[boardPos.getCol()][boardPos.getRow()].setTile(tile);
				cout << "TESTT:: " << tile.getLetter() << endl;
				currentWord.push_back(tile.getLetter());
				currentWordPosition.push_back(boardPos);
				currentWordTiles.push_back(tile);
				m_wordLength++;

				return VALID_POSITION;
			}

		}
	}
	return INVALID_POSITION;
}

CurrentWordResult Board::checkCurrentWord(int& points) {
	BoardPosition inicial(7, 7);
	string word;
	bool correcte = false;

	for (unsigned int i = 0; i < currentWord.size(); i++) {
		word += currentWord[i];
	}

	if (getFirst()) {
		unsigned int j = 0;

		while (!correcte && j < currentWordPosition.size()) {
			if (currentWordPosition[j] == inicial) {
				correcte = true;
			}
			else {
				j++;
			}
		}

		if (correcte) {
			if (m_wordLength < 2) {
				return INVALID_WORD_OF_ONE_LETTER;
			}
			else if (!m_dictionary.check(word)) {
				return INVALID_WORDS_NOT_IN_DICTIONARY;
			}
			else {
				m_isFirst = false;
				points = getTotalScore();
			}
		}
		else {
			return INVALID_START_NOT_IN_CENTER;
		}
	}
	else {
		if (m_wordLength < 2) {
			return INVALID_WORD_OF_ONE_LETTER;
		}
		else if (!m_dictionary.check(word)) {
			return INVALID_WORDS_NOT_IN_DICTIONARY;
		}
	}

	points = getTotalScore();

	return ALL_CORRECT;
}

int Board::getTotalScore() {
	currentScore = 0;
	bool dobleWord = false;
	bool tripleWord = false;

	for (int i = 0; i < m_wordLength; i++) {
		if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == DL) {
			currentScore += currentWordTiles[i].getScore() * 2;

		}
		else if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == TL) {
			currentScore += currentWordTiles[i].getScore() * 3;

		}
		else if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == DW) {
			currentScore += currentWordTiles[i].getScore();
			dobleWord = true;

		}
		else if (m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].getScore() == TW) {
			currentScore += currentWordTiles[i].getScore();
			tripleWord = true;

		}
		else {
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

void Board::sendCurrentWordToBoard() {
	cout << "test" << m_wordLength << endl;

	for (int i = 0; i < m_wordLength; i++) {
		m_cells[currentWordPosition[i].getCol()][currentWordPosition[i].getRow()].setTile(currentWordTiles[i]);
	}

	cout << "test2" << endl;

	removeCurrentWord();
	currentScore = 0;
	m_wordLength = 0;

	cout << "test3" << endl;
}

void Board::removeCurrentWord() {
	unsigned int i = 0;

	while (i <= currentWord.size()) {
		currentWordPosition.pop_back();
		currentWordTiles.pop_back();
		currentWord.pop_back();
		i++;
	}

	m_wordLength = 0;
}