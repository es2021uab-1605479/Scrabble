#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H

#include <stdio.h>

class BoardPosition {
public:
  BoardPosition(): m_iRow(-1), m_iCol(-1) {}
  BoardPosition(int col, int row): m_iRow(row), m_iCol(col) {}

  int getCol() const { return m_iCol; }
  int getRow() const { return m_iRow; }
  void setCol(int col) { m_iCol = col; }
  void setRow(int row) { m_iRow = row; }
  bool operator== (const BoardPosition& bp) const {
    return m_iRow == bp.m_iRow && m_iCol == bp.m_iCol;
  }

private:
  int m_iRow;
  int m_iCol;
};

#endif
