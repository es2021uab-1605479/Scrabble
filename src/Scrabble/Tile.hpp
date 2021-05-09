#ifndef TILE_HPP
#define TILE_HPP

class Tile {
public:
    Tile() : m_letter(' '), m_score(0) {}
    Tile(char letter, int score) : m_letter(letter), m_score(score) {}

    void setLetter(char letter) { m_letter = letter; }
    void setScore(int score) { m_score = score; }
    char getLetter() const { return m_letter; }
    int getScore() const { return m_score; }

private:
    char m_letter;
    unsigned int m_score;
};

#endif
