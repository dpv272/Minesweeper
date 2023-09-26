#ifndef _TILE_H_
#define _TILE_H_

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace sf;
using namespace std;

class Tile
{
public:
	Tile();
	Tile(int, int);
	Tile& operator=(const Tile&);
	Tile(const Tile&);

	bool isFlagged() const;
	bool isMine() const;
	bool isRevealed() const;

	int getAdjacentMine() const;

	void setAdjacentMine(int);
	void setFlag(bool);
	void setFlagTexture();
	void setHiddenTexture();
	void setMine(bool);
	void setMineTexture();
	void setRevealed(bool);
	void setRevealedTexture();

	Sprite& getSprite();

private:
	bool m_flagged = false;
	bool m_mine = false;
	bool m_revealed = false;

	int m_adjacentMine = 0;
	int m_col = 0;
	int m_row = 0;

	RectangleShape m_shape;
	Sprite m_sprite;

	Texture m_flaggedTexture;
	Texture m_hiddenTexture;
	Texture m_mineTexture;
	Texture m_revealedTexture;
};

#endif // !_TILE_H_
