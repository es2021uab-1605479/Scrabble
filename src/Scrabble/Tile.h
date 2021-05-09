//
//  Tile.hpp
//  Scrabble
//

#ifndef Tile_hpp
#define Tile_hpp


class Tile
{
public:
    Tile() { m_letter = ' ', m_score = 0; }
    Tile(char letter, int score) { m_letter = letter, m_score = score; }
    ~Tile() {}
    char getLetter() const { return m_letter; }
    int getScore() const { return m_score; }

private:
    char m_letter;
    unsigned int m_score;
};


#endif /* Tile_hpp */
