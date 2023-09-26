#ifndef _BOARD_H_
#define _BOARD_H_

#include "Tile.h"

class Board
{
public:
	Board(int, int, int);
	Board& operator=(const Board&);
	~Board();

	int getAdjacentMine(int, int);
	int getFlag();
	int getRevealed() const;

	Tile getTile(int, int);
	vector<vector<Tile>> tiles;
	vector<vector<Tile>> getTiles() const;

	void initBoard();
	void incrementFlag(int, int, bool);
	void resetBoard();
	void revealedTile(int, int);
	void setAdjacentMine();

	void drawFlag(RenderWindow&);
	void drawHidden(int, int, RenderWindow&);
	void drawMine(int, int, RenderWindow&);

private:
	int col = 0;
	int row = 0;
	int flag = 0;
	int mine = 0;
	int revealed = 0;

	RenderWindow m_window;
};

#endif // !_BOARD_H_
