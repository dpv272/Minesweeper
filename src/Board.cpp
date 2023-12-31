#include "../header/Board.h"

Board::Board(int rows, int cols, int mines)
{
	col = cols;
	row = rows;
	mine = mines;
	flag = 0;
	tiles.resize(row);

	for (int i = 0; i < row; i++)
	{
		tiles[i].resize(col);

		for (int j = 0; j < col; j++)
		{
			tiles[i][j] = Tile(i, j);
		}
	}
}

Board& Board::operator=(const Board& other)
{
	if (this != &other)
	{
		col = other.col;
		row = other.row;
		mine = other.mine;
		tiles = other.tiles;
	}

	return *this;
}

Board::~Board()
{
}

int Board::getAdjacentMine(int rows, int cols)
{
	int count = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int checkCol = cols + j;
			int checkRow = rows + i;

			if (i == 0 && j == 0)
				continue;

			if (checkRow >= 0 && checkRow < row && checkCol >= 0 && checkCol < col)
			{
				if (tiles[checkRow][checkCol].isMine())
					count++;
			}
		}
	}
	return count;
}

int Board::getFlag()
{
	return flag;
}

int Board::getRevealed() const
{
	return revealed;
}

Tile Board::getTile(int rows, int cols)
{
	return tiles[rows][cols];
}

vector<vector<Tile>> Board::getTiles() const
{
	return tiles;
}

void Board::initBoard()
{
	for (int i = 0; i < mine; i++)
	{
		int cols = rand() % col;
		int rows = rand() % row;

		if (tiles[rows][cols].isMine())
			i--;

		if (!tiles[rows][cols].isMine() && !tiles[rows][cols].isRevealed())
			tiles[rows][cols].setMine(true);
	}

	setAdjacentMine();
}

void Board::incrementFlag(int rows, int cols, bool isFlagged)
{
	if (isFlagged)
		flag++;
	else
		flag--;
}

void Board::resetBoard()
{
	flag = 0;
	revealed = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tiles[i][j].setFlag(false);
			tiles[i][j].setMine(false);
			tiles[i][j].setRevealed(false);
		}
	}

	initBoard();
}

void Board::revealedTile(int rows, int cols)
{
	Tile& tile = tiles[rows][cols];

	if (tile.isMine())
		return;

	if (tile.getAdjacentMine() == 0)
	{
		tile.setRevealed(true);
		revealed += 1;

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				int aroundCol = cols + j;
				int aroundRow = rows + i;

				if (aroundRow >= 0 && aroundRow < row && aroundCol >= 0 && aroundCol < col)
				{
					Tile& aroundTile = tiles[aroundRow][aroundCol];

					if (!aroundTile.isFlagged() && !aroundTile.isMine() && !aroundTile.isRevealed())
						revealedTile(aroundRow, aroundCol);
				}
			}
		}
	}
	else
	{
		tile.setRevealed(true);
		revealed += 1;
	}
}

void Board::setAdjacentMine()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int count = 0;

			for (int m = i - 1; m <= i + 1; m++)
			{
				for (int n = j - 1; n <= j + 1; n++)
				{
					if (m >= 0 && m < row && n >= 0 && n < col && tiles[m][n].isMine())
						count++;
				}
			}

			tiles[i][j].setAdjacentMine(count);
		}
	}
}

void Board::drawFlag(RenderWindow& window)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (tiles[i][j].isFlagged())
			{
				tiles[i][j].setFlagTexture();
				Sprite sprite = tiles[i][j].getSprite();
				sprite.setPosition(j * 32, i * 32);
				window.draw(sprite);
			}
		}
	}
}

void Board::drawHidden(int rows, int cols, RenderWindow& window)
{
	if (tiles[rows][cols].isRevealed())
	{
		tiles[rows][cols].setHiddenTexture();
		Sprite sprite = tiles[rows][cols].getSprite();
		sprite.setPosition(cols * 32, rows * 32);
		window.draw(sprite);
	}
}

void Board::drawMine(int rows, int cols, RenderWindow& window)
{
	if (tiles[rows][cols].isMine())
	{
		tiles[rows][cols].setMineTexture();
		Sprite sprite = tiles[rows][cols].getSprite();
		sprite.setPosition(cols * 32, rows * 32);
		window.draw(sprite);
	}
}
