#include "header/Board.h"

struct Player
{
	string name;
	int minutes;
	int seconds;
	int rank;
};

int main()
{
	vector<Player> player;

	int tileHeight = 32;
	int tileWidth = 32;

	ifstream file("assets/leaderboard.txt");
	string line;

	while (getline(file, line))
	{
		stringstream ss(line);
		string times, name;

		getline(ss, times, ',');
		getline(ss, name);

		stringstream timeStream(times);
		int minutes, seconds;
		char colon;

		timeStream >> minutes >> colon >> seconds;

		player.push_back({ name, minutes, seconds });
	}
	file.close();

	Font font;

	if (!font.loadFromFile("assets/mooli_font.ttf"))
		return 1;

	srand(time(NULL));

	int tileSize = 32;

	ifstream config("assets/config.txt");

	if (!config)
		return 1;

	vector<int> data;

	for (string line{}; getline(config, line);)
	{
		int var = stoi(line);
		data.push_back(var);
	}

	int n_col = data[0];
	int n_row = data[1];
	int n_mine = data[2];
	int num = n_col * n_row - n_mine;

	RenderWindow window(VideoMode(n_col * 32, n_row * 32 + 100), "Welcome");

	Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
	welcomeText.setStyle(Text::Bold | Text::Underlined);
	welcomeText.setFillColor(Color::White);
	welcomeText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150);
	welcomeText.setOrigin(welcomeText.getLocalBounds().width / 2.0f, welcomeText.getLocalBounds().height / 2.0f);

	Text promptText("Enter your name:", font, 20);
	promptText.setStyle(Text::Bold);
	promptText.setFillColor(Color::White);
	promptText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 75);
	promptText.setOrigin(promptText.getLocalBounds().width / 2.0f, promptText.getLocalBounds().height / 2.0f);

	Text inputText("", font, 18);
	inputText.setStyle(Text::Bold);
	inputText.setFillColor(Color::Yellow);
	inputText.setOrigin(inputText.getLocalBounds().width / 2.0f, inputText.getLocalBounds().height / 2.0f);
	inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);

	Text cursor("|", font, 18);
	cursor.setStyle(Text::Bold);
	cursor.setFillColor(Color::Yellow);
	cursor.setOrigin(0.0f, cursor.getLocalBounds().height / 2.0f);

	string userInput;

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return 0;
			}
			else if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == 8)
				{
					if (!userInput.empty())
						userInput.pop_back();
				}
				else if (isalpha(event.text.unicode))
				{
					if (userInput.length() == 0)
						userInput.push_back(toupper(event.text.unicode));
					else if (userInput.length() < 10)
						userInput.push_back(tolower(event.text.unicode));

					inputText.setString(userInput);
					inputText.setOrigin(inputText.getLocalBounds().width / 2.0f, inputText.getLocalBounds().height / 2.0f);
					inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
				}
			}
			else if (event.type == Event::KeyPressed and userInput.length() > 0)
			{
				if (event.key.code == Keyboard::Return)
					window.close();
			}
		}

		window.clear(Color::Black);

		inputText.setString(userInput + cursor.getString());

		window.draw(welcomeText);
		window.draw(promptText);
		window.draw(inputText);

		window.display();
	}

	Board gameBoard(n_row, n_col, n_mine);

	gameBoard.initBoard();

	vector<vector<Tile>> tiles = gameBoard.getTiles();

	RenderWindow gameWindow(VideoMode(n_col * 32, n_row * 32 + 100), "Minesweeper");

	Texture t_n1;
	if (!t_n1.loadFromFile("assets/images/number_1.png"))
		return 1;

	vector<Sprite> v_n1;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n1(t_n1);

			s_n1.setPosition(j * 32, i * 32);
			v_n1.push_back(s_n1);
		}
	}

	Texture t_n2;
	if (!t_n2.loadFromFile("assets/images/number_2.png"))
		return 1;

	vector<Sprite> v_n2;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n2(t_n2);

			s_n2.setPosition(j * 32, i * 32);
			v_n2.push_back(s_n2);
		}
	}

	Texture t_n3;
	if (!t_n3.loadFromFile("assets/images/number_3.png"))
		return 1;

	vector<Sprite> v_n3;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n3(t_n3);

			s_n3.setPosition(j * 32, i * 32);
			v_n3.push_back(s_n3);
		}
	}

	Texture t_n4;
	if (!t_n4.loadFromFile("assets/images/number_4.png"))
		return 1;

	vector<Sprite> v_n4;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n4(t_n4);

			s_n4.setPosition(j * 32, i * 32);
			v_n4.push_back(s_n4);
		}
	}

	Texture t_n5;
	if (!t_n5.loadFromFile("assets/images/number_5.png"))
		return 1;

	vector<Sprite> v_n5;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n5(t_n5);

			s_n5.setPosition(j * 32, i * 32);
			v_n5.push_back(s_n5);
		}
	}

	Texture t_n6;
	if (!t_n6.loadFromFile("assets/images/number_6.png"))
		return 1;

	vector<Sprite> v_n6;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n6(t_n6);

			s_n6.setPosition(j * 32, i * 32);
			v_n6.push_back(s_n6);
		}
	}

	Texture t_n7;
	if (!t_n7.loadFromFile("assets/images/number_7.png"))
		return 1;

	vector<Sprite> v_n7;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n7(t_n7);

			s_n7.setPosition(j * 32, i * 32);
			v_n7.push_back(s_n7);
		}
	}

	Texture t_n8;
	if (!t_n8.loadFromFile("assets/images/number_8.png"))
		return 1;

	vector<Sprite> v_n8;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_n8(t_n8);

			s_n8.setPosition(j * 32, i * 32);
			v_n8.push_back(s_n8);
		}
	}

	Texture t_flag;
	if (!t_flag.loadFromFile("assets/images/flag.png"))
		return 1;

	vector<Sprite> v_flag;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_flag(t_flag);

			s_flag.setPosition(j * 32, i * 32);
			v_flag.push_back(s_flag);
		}
	}

	Texture t_mine;
	if (!t_mine.loadFromFile("assets/images/mine.png"))
		return 1;

	vector<Sprite> v_mine;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_mine(t_mine);

			s_mine.setPosition(j * 32, i * 32);
			v_mine.push_back(s_mine);
		}
	}

	Texture t_revealed;
	if (!t_revealed.loadFromFile("assets/images/revealed.png"))
		return 1;

	vector<Sprite> v_revealed;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_revealed(t_revealed);

			s_revealed.setPosition(j * 32, i * 32);
			v_revealed.push_back(s_revealed);
		}
	}

	Texture t_tile;
	if (!t_tile.loadFromFile("assets/images/tile.png"))
		return 1;

	vector<Sprite> v_tile;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			Sprite s_tile(t_tile);

			s_tile.setPosition(j * 32, i * 32);
			v_tile.push_back(s_tile);
		}
	}

	Texture t_face;
	if (!t_face.loadFromFile("assets/images/face.png"))
		return 1;

	Sprite s_face(t_face);
	s_face.setPosition(n_col / 2.0 * 32 - 32, (n_row + 0.5f) * 32);

	Texture t_faceLose;
	if (!t_faceLose.loadFromFile("assets/images/face_lose.png"))
		return 1;

	Texture t_faceWin;
	if (!t_faceWin.loadFromFile("assets/images/face_win.png"))
		return 1;

	Texture t_debug;
	if (!t_debug.loadFromFile("assets/images/debug.png"))
		return 1;

	Sprite s_debug(t_debug);
	s_debug.setPosition(n_col * 32 - 304, (n_row + 0.5f) * 32);

	Texture t_pause;
	if (!t_pause.loadFromFile("assets/images/pause.png"))
		return 1;

	Sprite s_pause(t_pause);
	s_pause.setPosition(n_col * 32 - 239, (n_row + 0.5f) * 32);

	Texture t_play;
	if (!t_play.loadFromFile("assets/images/play.png"))
		return 1;

	Texture t_leaderboard;
	if (!t_leaderboard.loadFromFile("assets/images/leaderboard.png"))
		return 1;

	Sprite s_leaderboard(t_leaderboard);
	s_leaderboard.setPosition(n_col * 32 - 174, (n_row + 0.5f) * 32);

	Texture t_digits;
	if (!t_digits.loadFromFile("assets/images/digits.png"))
		return 1;

	Sprite s_min1(t_digits);
	s_min1.setTextureRect(IntRect(0, 0, 21, 32));
	s_min1.setPosition(n_col * 32 - 97, (n_row + 0.5f) * 32 + 16);

	Sprite s_min2(t_digits);
	s_min2.setTextureRect(IntRect(21, 0, 21, 32));
	s_min2.setPosition(n_col * 32 - 76, (n_row + 0.5f) * 32 + 16);

	Sprite s_sec1(t_digits);
	s_sec1.setTextureRect(IntRect(0, 0, 21, 32));
	s_sec1.setPosition(n_col * 32 - 54, (n_row + 0.5f) * 32 + 16);

	Sprite s_sec2(t_digits);
	s_sec2.setTextureRect(IntRect(21, 0, 21, 32));
	s_sec2.setPosition(n_col * 32 - 33, (n_row + 0.5f) * 32 + 16);

	Sprite s_flag1(t_digits);
	s_flag1.setTextureRect(IntRect(0, 0, 21, 32));
	s_flag1.setPosition(33, (n_row + 0.5f) * 32 + 16);

	Sprite s_flag2(t_digits);
	s_flag2.setTextureRect(IntRect(0, 0, 21, 32));
	s_flag2.setPosition(54, (n_row + 0.5f) * 32 + 16);

	Sprite s_flag3(t_digits);
	s_flag3.setTextureRect(IntRect(0, 0, 21, 32));
	s_flag3.setPosition(75, (n_row + 0.5f) * 32 + 16);

	Clock clock;
	Time totalTime = Time::Zero;

	bool isPaused = false;
	bool debug = false;
	int winCount = 0;

	Time winTime = Time::Zero;

	bool hasWon = false;
	bool lose = false;

	while (gameWindow.isOpen())
	{
		Event event;

		while (gameWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				gameWindow.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
			{
				for (int i = 0; i < n_col * n_row; i++)
				{
					int col = i % n_col;
					int row = i / n_col;

					float tileX = col * tileSize;
					float tileY = row * tileSize;

					if (event.mouseButton.x >= tileX && event.mouseButton.x < tileX + tileSize && event.mouseButton.y >= tileY && event.mouseButton.y < tileY + tileSize)
					{
						if (!gameBoard.getTile(row, col).isRevealed())
						{
							bool isFlagged = !tiles[row][col].isFlagged();

							tiles[row][col].setFlag(isFlagged);
							gameBoard.incrementFlag(row, col, isFlagged);
						}
					}
				}
			}
			else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				for (int i = 0; i < n_col * n_row; i++)
				{
					int col = i % n_col;
					int row = i / n_col;

					float tileX = col * tileSize;
					float tileY = row * tileSize;

					if (event.mouseButton.x >= tileX && event.mouseButton.x < tileX + tileSize && event.mouseButton.y >= tileY && event.mouseButton.y < tileY + tileSize)
					{
						if (gameBoard.getTile(row, col).isMine() && !tiles[row][col].isFlagged())
						{
							s_face.setTexture(t_faceLose);
							lose = true;
							isPaused = true;
						}

						if (!gameBoard.getTile(row, col).isRevealed() && !tiles[row][col].isFlagged())
						{
							gameBoard.revealedTile(row, col);
							winCount += 1;

							if (!hasWon && gameBoard.getRevealed() == num)
							{
								hasWon = true;
								s_face.setTexture(t_faceWin);
								gameWindow.draw(s_face);
								gameWindow.display();
							}

							if (hasWon)
							{
								int totalSeconds = totalTime.asSeconds();
								int minutes = totalSeconds / 60;
								int seconds = totalSeconds % 60;
								int height = n_row * 16 + 50;
								int width = n_col * 16;

								RenderWindow leaderboardWindow(VideoMode(n_col * 16, n_row * 16 + 50), "Leaderboard");

								Text leaderboardText("LEADERBOARD", font, 20);
								leaderboardText.setStyle(Text::Bold | Text::Underlined);
								leaderboardText.setFillColor(Color::White);
								leaderboardText.setPosition(width / 2.0f, height / 2.0f - 120);
								leaderboardText.setOrigin(leaderboardText.getGlobalBounds().width / 2.0f, leaderboardText.getGlobalBounds().height / 2.0f);

								player.push_back({ userInput,minutes,seconds });

								sort(player.begin(), player.end(), [](const Player& p1, const Player& p2)
									{
										if (p1.minutes == p2.minutes)
											return p1.seconds < p2.seconds;
										else
											return p1.minutes < p2.minutes;
									});

								if (player.size() > 5)
									player.pop_back();

								ofstream file("assets/leaderboard.txt");

								if (file.is_open())
								{
									for (const auto& p : player)
									{
										file << setfill('0') << setw(2) << p.minutes << ":" << setfill('0') << setw(2) << p.seconds << "," << p.name << endl;
										file.close();
									}
								}
								file.close();

								string contents;

								for (int i = 0; i < player.size(); i++)
									player[i].rank = i + 1;

								for (const auto& p : player)
								{
									string row = to_string(p.rank) + ".\t";

									stringstream ss;

									ss << setfill('0') << setw(2) << p.minutes << ":" << setfill('0') << setw(2) << p.seconds;
									row += ss.str() + "\t" + p.name + "\n\n";
									contents += row;
								}

								Text leaderboardContent(contents, font, 18);
								leaderboardContent.setStyle(Text::Bold);
								leaderboardContent.setFillColor(Color::White);
								leaderboardContent.setPosition(width / 2.0f, height / 2.0f + 20);
								leaderboardContent.setOrigin(leaderboardContent.getGlobalBounds().width / 2.0f, leaderboardContent.getGlobalBounds().height / 2.0f);

								while (leaderboardWindow.isOpen())
								{
									Event ev;

									while (leaderboardWindow.pollEvent(ev))
									{
										if (ev.type == Event::Closed)
											leaderboardWindow.close();

										leaderboardWindow.clear(Color::Black);
										leaderboardWindow.draw(leaderboardText);
										leaderboardWindow.draw(leaderboardContent);
										leaderboardWindow.display();
									}
								}
							}
						}
					}
				}

				if (s_face.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					totalTime = Time::Zero;
					totalTime -= clock.getElapsedTime();
					s_face.setTexture(t_face);

					gameBoard.resetBoard();

					for (int i = 0; i < n_col * n_row; i++)
					{
						int col = i % n_col;
						int row = i / n_row;

						if (tiles[row][col].isFlagged())
							tiles[row][col].setFlag(false);
					}

					s_pause.setTexture(t_pause);
					isPaused = false;
					lose = false;
					winCount = 0;
				}

				if (s_debug.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					debug = !debug;

				if (s_pause.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					isPaused = !isPaused;

					if (isPaused)
					{
						s_pause.setTexture(t_play);
						totalTime += clock.getElapsedTime();
					}
					else
					{
						s_pause.setTexture(t_pause);
						totalTime -= clock.getElapsedTime();
					}
				}

				if (s_leaderboard.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					isPaused = true;
					s_pause.setTexture(t_play);

					gameWindow.draw(s_pause);
					gameWindow.display();

					int height = n_row * 16 + 50;
					int width = n_col * 16;

					RenderWindow leaderboardWindow(VideoMode(n_col * 16, n_row * 16 + 50), "Leaderboard");

					Text leaderboardText("LEADERBOARD", font, 20);
					leaderboardText.setStyle(Text::Bold | Text::Underlined);
					leaderboardText.setFillColor(Color::White);
					leaderboardText.setPosition(width / 2.0f, height / 2.0f - 120);
					leaderboardText.setOrigin(leaderboardText.getGlobalBounds().width / 2.0f, leaderboardText.getGlobalBounds().height / 2.0f);

					string contents;

					for (int i = 0; i < player.size(); i++)
						player[i].rank = i + 1;

					for (const auto& p : player)
					{
						string row = to_string(p.rank) + ".\t";

						stringstream ss;

						ss << setfill('0') << setw(2) << p.minutes << ":" << setfill('0') << setw(2) << p.seconds;
						row += ss.str() + "\t" + p.name + "\n\n";
						contents += row;
					}

					Text leaderboardContent(contents, font, 18);
					leaderboardContent.setStyle(Text::Bold);
					leaderboardContent.setFillColor(Color::White);
					leaderboardContent.setPosition(width / 2.0f, height / 2.0f + 20);
					leaderboardContent.setOrigin(leaderboardContent.getGlobalBounds().width / 2.0f, leaderboardContent.getGlobalBounds().height / 2.0f);

					while (leaderboardWindow.isOpen())
					{
						Event ev;

						while (leaderboardWindow.pollEvent(ev))
						{
							if (ev.type == Event::Closed)
								leaderboardWindow.close();

							leaderboardWindow.clear(Color::Black);
							leaderboardWindow.draw(leaderboardText);
							leaderboardWindow.draw(leaderboardContent);
							leaderboardWindow.display();
						}
					}
				}
			}
		}

		if (!isPaused)
		{
			totalTime += clock.getElapsedTime();
			clock.restart();
		}

		int minutes = totalTime.asSeconds() / 60;
		int seconds = static_cast<int>(totalTime.asSeconds()) % 60;

		s_min1.setTextureRect(IntRect(minutes / 10 * 21, 0, 21, 32));
		s_min2.setTextureRect(IntRect(minutes % 10 * 21, 0, 21, 32));
		s_sec1.setTextureRect(IntRect(seconds / 10 * 21, 0, 21, 32));
		s_sec2.setTextureRect(IntRect(seconds % 10 * 21, 0, 21, 32));

		int remainMines = n_mine - gameBoard.getFlag();

		s_flag1.setTextureRect(IntRect(remainMines / 100 * 21, 0, 21, 32));
		s_flag2.setTextureRect(IntRect(remainMines / 10 % 10 * 21, 0, 21, 32));
		s_flag3.setTextureRect(IntRect(remainMines % 10 * 21, 0, 21, 32));

		gameWindow.clear(Color::White);
		gameWindow.draw(s_face);
		gameWindow.draw(s_leaderboard);
		gameWindow.draw(s_debug);
		gameWindow.draw(s_pause);

		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				int index = i * n_col + j;
				int adjacentMine = 0;

				if (tiles[i][j].isFlagged())
				{
					gameBoard.drawHidden(i, j, gameWindow);
					gameWindow.draw(v_flag[index]);
				}
				else if (lose)
				{
					gameBoard.drawHidden(i, j, gameWindow);
					if (tiles[i][j].isFlagged())
					{
						gameBoard.drawMine(i, j, gameWindow);
						gameWindow.draw(v_flag[index]);
					}
					else
						gameBoard.drawMine(i, j, gameWindow);

					isPaused = true;
				}
				else if (debug)
				{
					if (tiles[i][j].isFlagged())
						continue;
					else
					{
						gameWindow.draw(v_tile[index]);
						gameBoard.drawMine(i, j, gameWindow);
					}
				}
				else if (isPaused)
					gameBoard.drawHidden(i, j, gameWindow);
				else if (gameBoard.getTile(i, j).isRevealed())
				{
					gameWindow.draw(v_revealed[index]);
					adjacentMine = gameBoard.getAdjacentMine(i, j);

					if (adjacentMine == 1)
						gameWindow.draw(v_n1[index]);
					else if (adjacentMine == 2)
						gameWindow.draw(v_n2[index]);
					else if (adjacentMine == 3)
						gameWindow.draw(v_n3[index]);
					else if (adjacentMine == 4)
						gameWindow.draw(v_n4[index]);
					else if (adjacentMine == 5)
						gameWindow.draw(v_n5[index]);
					else if (adjacentMine == 6)
						gameWindow.draw(v_n6[index]);
					else if (adjacentMine == 7)
						gameWindow.draw(v_n7[index]);
					else if (adjacentMine == 8)
						gameWindow.draw(v_n8[index]);
				}
				else
					gameBoard.drawHidden(i, j, gameWindow);
			}
		}

		gameWindow.draw(s_min1);
		gameWindow.draw(s_min2);
		gameWindow.draw(s_sec1);
		gameWindow.draw(s_sec2);

		gameWindow.draw(s_flag1);
		gameWindow.draw(s_flag2);
		gameWindow.draw(s_flag3);

		gameWindow.display();
	}

	return 0;
}
