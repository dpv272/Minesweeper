#include "../header/Tile.h"

Tile::Tile()
{
	m_mine = false;
	m_revealed = false;

	m_sprite.setTexture(m_hiddenTexture);
}

Tile::Tile(int row, int col)
{
	m_col = col;
	m_row = row;
	m_mine = false;
	m_adjacentMine = 0;

	m_sprite.setTexture(m_hiddenTexture);
}

Tile& Tile::operator=(const Tile& other)
{
	if (this == &other)
		return *this;

	m_mine = other.m_mine;
	m_revealed = other.m_revealed;

	return *this;
}

Tile::Tile(const Tile& other)
{
	m_mine = other.m_mine;
	m_revealed = other.m_revealed;
}

bool Tile::isFlagged() const
{
	return m_flagged;
}

bool Tile::isMine() const
{
	return m_mine;
}

bool Tile::isRevealed() const
{
	return m_revealed;
}

int Tile::getAdjacentMine() const
{
	return m_adjacentMine;
}

void Tile::setAdjacentMine(int number)
{
	m_adjacentMine = number;
}

void Tile::setFlag(bool flag)
{
	m_flagged = flag;
}

void Tile::setFlagTexture()
{
	m_sprite.setTexture(m_flaggedTexture);
}

void Tile::setHiddenTexture()
{
	m_sprite.setTexture(m_hiddenTexture);
}

void Tile::setMine(bool mine)
{
	m_mine = mine;
}

void Tile::setMineTexture()
{
	m_sprite.setTexture(m_mineTexture);
}

void Tile::setRevealed(bool revealed)
{
	m_revealed = revealed;
}

void Tile::setRevealedTexture()
{
	m_sprite.setTexture(m_revealedTexture);
}

Sprite& Tile::getSprite()
{
	return m_sprite;
}
