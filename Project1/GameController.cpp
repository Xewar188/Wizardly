#include "GameController.h"
#include "Board.h"
#include "Map.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Chest.h"
#include "Warrior.h"
#include "Vendor.h"
#include "Artifact.h"
#include "Mage.h"
#include "StartTile.h"
#include "Projectile.h"
#include "Healpoint.h"
#include "HealthVendor.h"
#include "AttackSpeedVendor.h"
#include "Wall.h"
#include "Plains.h"
#include "Stone.h"
#include "SpeedShrine.h"
#include "UsedShrine.h"

sf::RenderWindow GameController::window;
Board GameController::boardComplex[BOARD_NUMBER][BOARD_NUMBER];

Event GameController::msg;
Player GameController::player;
Map GameController::mapComplex;
int GameController::xboard, GameController::yboard;
sf::Font* GameController::font;
bool GameController::didPlayerWin;
bool GameController::manualMode;

std::vector<sf::RectangleShape> GameController::playerSpeed;
std::vector<sf::RectangleShape> GameController::playerStrength;
std::vector<sf::RectangleShape> GameController::playerGold;
sf::Text GameController::playerGoldText;
sf::Text GameController::playerSpeedText;
sf::Text GameController::playerStrengthText;

void GameController::prepareNewGame()
{
	
	manualMode = false;
	didPlayerWin = false;
	xboard = 0;
	yboard = 0;
	prepareBoards();

	std::stringstream temp;
	temp << player.getVel() - 5 << " " << player.getStrength() - 2 << " " << player.getGold();
	std::string temps;
	temp >> temps;
	playerSpeedText.setString(temps);
	temp >> temps;
	playerStrengthText.setString(temps);
	temp >> temps;
	playerGoldText.setString(temps);
}

void GameController::prepareBoards()
{
	srand((int)time(NULL));
	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++)
			boardComplex[i][j].clearBoard();
	player.clearPlayer();
	createBasicBoards();
	createStatIcons();
	openPassages();
	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++)
		{
			mapComplex.maps[i][j] = MapTile(boardComplex[i][j], window.getSize());
			boardComplex[i][j].map = &mapComplex.maps[i][j];
		}
	emplaceArtifacts();
	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++)
		{
			if (j == 0 && i == 0)
				continue;
			emplaceShrines(boardComplex[i][j]);
			emplaceMages(boardComplex[i][j]);
			emplaceWarriors(boardComplex[i][j]);
			emplaceHealing(boardComplex[i][j]);
			emplaceVendors(boardComplex[i][j]);
			emplaceChests(boardComplex[i][j]);
		}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			boardComplex[0][0].changeCell(COLUMNS_NUMBER / 2 - 1 + i, ROWS_NUMBER / 2 - 1 + j, new Plains(&boardComplex[0][0], COLUMNS_NUMBER / 2 - 1 + i, ROWS_NUMBER / 2 - 1 + j));

	boardComplex[0][0].map->setShrine(5);
	boardComplex[0][0].map->update();
	boardComplex[0][0].changeCell(COLUMNS_NUMBER / 2, ROWS_NUMBER / 2, new StartTile(&boardComplex[0][0], COLUMNS_NUMBER / 2, ROWS_NUMBER / 2));
	mapComplex.maps[0][0].find();


	player = Player((float) window.getSize().y / 3 / ROWS_NUMBER,
		(float) window.getSize().y / 3 / ROWS_NUMBER,
		(float) window.getSize().x / 2 - window.getSize().y / 3 / ROWS_NUMBER / 2,
		(float) window.getSize().y / 2 - window.getSize().y / 3 / ROWS_NUMBER / 2,
		Color(0, 0, 0),
		&boardComplex[xboard][yboard]);

	boardComplex[0][0].entity.insert(boardComplex[0][0].getEntityBeginPointer(), &player);
}

void GameController::createBasicBoards()
{
	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++) {
			for (int x = 0; x < COLUMNS_NUMBER; x++)
			{
				boardComplex[i][j].board[x][0] = new Wall(&boardComplex[i][j], x, 0);
			}
			for (int x = 1; x < ROWS_NUMBER - 1; x++)
			{

				boardComplex[i][j].board[0][x] = new Wall(&boardComplex[i][j], 0, x);
				for (int y = 1; y < COLUMNS_NUMBER - 1; y++)
					boardComplex[i][j].board[y][x] = new Plains(&boardComplex[i][j], y, x);
				boardComplex[i][j].board[COLUMNS_NUMBER - 1][x] = new Wall(&boardComplex[i][j], COLUMNS_NUMBER - 1, x);

			}
			for (int x = 0; x < COLUMNS_NUMBER; x++)
			{
				boardComplex[i][j].board[x][ROWS_NUMBER - 1] = new Wall(&boardComplex[i][j], x, ROWS_NUMBER - 1);
			}
		}
	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++)
			for (int k = 0; k < 130; k++)
			{
				int x = rand() % (COLUMNS_NUMBER - 2) + 1;
				int y = rand() % (ROWS_NUMBER - 2) + 1;
				boardComplex[i][j].changeCell(x, y, new Stone(&boardComplex[i][j], x, y));
			}
}

void GameController::createStatIcons()
{
	playerSpeed.clear();
	playerStrength.clear();
	playerGold.clear();

	int cellWidth = (int) boardComplex[0][0].getCellWidth();
	int cellHeight = (int) boardComplex[0][0].getCellHeight();
	playerSpeed.push_back(RectangleShape(Vector2f((float) cellWidth / 3, (float) cellHeight * 2 / 3)));
	playerSpeed.push_back(RectangleShape(Vector2f((float) cellWidth * 2 / 3, (float) cellHeight / 3)));
	playerSpeed[0].setPosition((float)(cellWidth / 4),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 3));
	playerSpeed[1].setPosition((float)(cellWidth / 4),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 2 + cellHeight / 3));
	playerSpeed[0].setFillColor(Color(0, 153, 255));
	playerSpeed[1].setFillColor(Color(0, 153, 255));

	playerStrength.push_back(RectangleShape(Vector2f((float) cellWidth * 2 / 3, (float) cellHeight * 2 / 3)));
	playerStrength.push_back(RectangleShape(Vector2f((float) cellWidth / 6, (float) cellHeight / 3)));
	playerStrength[0].setPosition((float)(cellWidth * 9 / 4),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 2 + 2));
	playerStrength[1].setPosition((float)(cellWidth * 9 / 4 + cellWidth * 2 / 3),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 2 + cellHeight / 3 + 2));
	playerStrength[0].setFillColor(Color(51, 204, 51));
	playerStrength[1].setFillColor(Color(51, 204, 51));

	playerGold.push_back(RectangleShape(Vector2f((float) cellWidth / 2 * 2 / 3, (float) cellHeight * 2 / 3)));
	playerGold.push_back(RectangleShape(Vector2f((float) cellWidth / 2 * 2 / 3, (float) cellHeight * 1 / 2)));
	playerGold[0].setPosition((float)(boardComplex[0][0].getCell(COLUMNS_NUMBER - 2, ROWS_NUMBER - 1)->getX() + cellWidth / 4),
		(float)(boardComplex[0][0].getCell(COLUMNS_NUMBER - 2, ROWS_NUMBER - 1)->getY() + cellHeight / 6));
	playerGold[0].setFillColor(Color(255, 225, 0));
	playerGold[1].setPosition((float)(boardComplex[0][0].getCell(COLUMNS_NUMBER - 2, ROWS_NUMBER - 1)->getX() + cellWidth / 4 - playerGold[1].getSize().x - 1),
		(float)(boardComplex[0][0].getCell(COLUMNS_NUMBER - 2, ROWS_NUMBER - 1)->getY() + cellHeight / 3));
	playerGold[1].setFillColor(Color(255, 225, 0));

	playerSpeedText.setFont(*font);
	playerStrengthText.setFont(*font);
	playerGoldText.setFont(*font);

	playerSpeedText.setCharacterSize(cellHeight * 2 / 3);
	playerStrengthText.setCharacterSize(cellHeight * 2 / 3);
	playerGoldText.setCharacterSize(cellHeight * 2 / 3);

	playerSpeedText.setPosition((float)(cellWidth * 5 / 4),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 3 + 2));
	playerStrengthText.setPosition((float)(cellWidth * 13 / 4),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 3 + 2));
	playerGoldText.setPosition((float)(boardComplex[0][0].getCell(COLUMNS_NUMBER - 1, ROWS_NUMBER - 1)->getX() - cellWidth / 4),
		(float)((ROWS_NUMBER - 1) * cellHeight + cellHeight / 3 + 2));
}

void GameController::openPassages()
{
	int temp;
	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++)
		{

			temp = rand() % 2;
			boardComplex[i][j].changeOpen(true, 2 + temp);
			boardComplex[i][j].opener[1 + temp] = true;
			if (temp == 1)
			{
				boardComplex[i][(j + 1) % BOARD_NUMBER].changeOpen(true, 1);
				boardComplex[i][(j + 1) % BOARD_NUMBER].opener[0] = true;
			}
			else
			{
				boardComplex[(i + 1) % BOARD_NUMBER][j].changeOpen(true, 4);
				boardComplex[(i + 1) % BOARD_NUMBER][j].opener[3] = true;
			}
			if (rand() % 3 == 0)
			{
				temp = 1 - temp;
				boardComplex[i][j].changeOpen(true, 2 + temp);
				boardComplex[i][j].opener[1 + temp] = true;
				if (temp == 1)
				{
					boardComplex[i][(j + 1) % BOARD_NUMBER].changeOpen(true, 1);
					boardComplex[i][(j + 1) % BOARD_NUMBER].opener[0] = true;
				}
				else
				{
					boardComplex[(i + 1) % BOARD_NUMBER][j].changeOpen(true, 4);
					boardComplex[(i + 1) % BOARD_NUMBER][j].opener[3] = true;
				}
			}

		}
}

void GameController::emplaceShrines(Board& target)
{
	if (rand() % 15 == 0)
	{
		int k;
		int x = 0;
		int y = 1;

		k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

		while (k > 0)
		{

			x++;
			if (x >= COLUMNS_NUMBER - 2)
			{
				y++;
				x = 1;
			}
			if (y >= ROWS_NUMBER - 2)
				y = 1;
			if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
			{
				k--;

			}

		}
		target.map->setShrine(1);
		target.map->update();
		target.changeCell(x, y, new SpeedShrine(&target, x, y));
		target.board[x][y]->setFilled(true);
		return;
	}
	if (rand() % 10 == 0)
	{
		int k;
		int x = 0;
		int y = 1;

		k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

		while (k > 0)
		{

			x++;
			if (x >= COLUMNS_NUMBER - 2)
			{
				y++;
				x = 1;
			}
			if (y >= ROWS_NUMBER - 2)
				y = 1;
			if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
			{
				k--;

			}

		}
		target.map->setShrine(2);
		target.map->update();
		target.changeCell(x, y, new SpeedShrine(&target, x, y));
		target.board[x][y]->setFilled(true);
	}
}

void GameController::emplaceArtifacts()
{
	int number = 4;
	while (number > 0)
	{
		int i = rand() % BOARD_NUMBER;
		int j = rand() % BOARD_NUMBER;
		while (boardComplex[i][j].map->hasShrine() || (i == 0 && j == 0))
		{
			i = rand() % BOARD_NUMBER;
			j = rand() % BOARD_NUMBER;
		}
		int k;
		int x = 0;
		int y = 1;

		k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

		while (k > 0)
		{

			x++;
			if (x >= COLUMNS_NUMBER - 2)
			{
				y++;
				x = 1;
			}
			if (y >= ROWS_NUMBER - 2)
				y = 1;
			if (!boardComplex[i][j].getCell(x, y)->isCellTangible() && !boardComplex[i][j].getCell(x, y)->isFilled())
			{
				k--;

			}

		}
		boardComplex[i][j].map->setShrine(3);
		boardComplex[i][j].map->update();
		boardComplex[i][j].changeCell(x, y, new  UsedShrine(&boardComplex[i][j], x, y));
		boardComplex[i][j].board[x][y]->setFilled(true);
		boardComplex[i][j].entity.push_back(new Artifact((float) window.getSize().y * 2 / 3 / ROWS_NUMBER,
			(float) window.getSize().y * 2 / 3 / ROWS_NUMBER,
			boardComplex[i][j].getCell(x, y)->getX() + boardComplex[i][j].getCellWidth() / 2 - window.getSize().y / 6 / ROWS_NUMBER,
			boardComplex[i][j].getCell(x, y)->getY() + boardComplex[i][j].getCellHeight() / 2 - window.getSize().y / 6 / ROWS_NUMBER,
			Color(255 * (rand() % 2), 255 * (rand() % 2), 255 * (rand() % 2)),
			&boardComplex[i][j], number - 1));
		number--;
	}
}

void GameController::emplaceMages(Board& target)
{
			int temp = rand() % 7;
			for (int z = 0; z < temp; z++)
			{
				int k;
				int x = 0;
				int y = 1;

				k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

				while (k > 0)
				{

					x++;
					if (x >= COLUMNS_NUMBER - 2)
					{
						y++;
						x = 1;
					}
					if (y >= ROWS_NUMBER - 2)
						y = 1;
					if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
					{
						k--;

					}

				}
				Weapon* chosenWeapon = NULL;
				switch (rand() % 3 + 1)
				{
				case 1:
					chosenWeapon = new Flamethrower();
					break;
				case 2:
					chosenWeapon = new Fireball();
					break;
				case 3:
					chosenWeapon = new MagicBolt();
					break;
				}
				target.entity.push_back(new Mage((float) window.getSize().y / 3 / ROWS_NUMBER,
					(float) window.getSize().y / 3 / ROWS_NUMBER,
					target.getCell(x, y)->getX() + target.getCellWidth() / 3,
					target.getCell(x, y)->getY() + target.getCellHeight() / 3,
					Color::White,
					&target, chosenWeapon));
				target.board[x][y]->setFilled(true);
			}
		
}

void GameController::emplaceWarriors(Board& target)
{
	int temp = rand() % 5;
	for (int z = 0; z < temp; z++)
	{
		int k;
		int x = 0;
		int y = 1;

		k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

		while (k > 0)
		{

			x++;
			if (x >= COLUMNS_NUMBER - 2)
			{
				y++;
				x = 1;
			}
			if (y >= ROWS_NUMBER - 2)
				y = 1;
			if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
			{
				k--;
			}

		}

		target.entity.push_back(new Warrior((float) window.getSize().y / 2 / ROWS_NUMBER,
			(float) window.getSize().y / 2 / ROWS_NUMBER,
			target.getCell(x, y)->getX() + target.getCellWidth() / 4,
			target.getCell(x, y)->getY() + target.getCellHeight() / 4,
			Color::White,
			Color(195, 194, 193),
			&target));
		target.board[x][y]->setFilled(true);
	}
}

void GameController::emplaceHealing(Board& target)
{
	
	if (rand() % 4 == 0)
	{
		int k;
		int x = 0;
		int y = 1;

		k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

		while (k > 0)
		{

			x++;
			if (x >= COLUMNS_NUMBER - 2)
			{
				y++;
				x = 1;
			}
			if (y >= ROWS_NUMBER - 2)
				y = 1;
			if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
			{
				k--;

			}

		}
		target.entity.push_back(new Healpoint((float) window.getSize().y / 2 / ROWS_NUMBER,
			(float) window.getSize().y / 2 / ROWS_NUMBER,
			target.getCell(x, y)->getX() + target.getCellWidth() / 2 * (rand() % 2),
			target.getCell(x, y)->getY() + target.getCellHeight() / 2 * (rand() % 2),
			&target));
		target.board[x][y]->setFilled(true);
	}
		
}

void GameController::emplaceVendors(Board& target)
{
		if (rand() % 7 == 0)
		{
			int k;
			int x = 0;
			int y = 1;

			k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

			while (k > 0)
			{

				x++;
				if (x >= COLUMNS_NUMBER - 2)
				{
					y++;
					x = 1;
				}
				if (y >= ROWS_NUMBER - 2)
					y = 1;
				if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
				{
					k--;

				}

			}
			if (rand() % 2 == 0)
				target.entity.push_back(new HealthVendor((float) window.getSize().y / 2 / ROWS_NUMBER,
					(float) window.getSize().y / 2 / ROWS_NUMBER,
					target.getCell(x, y)->getX() + target.getCellWidth() / 2 * (rand() % 2),
					target.getCell(x, y)->getY() + target.getCellHeight() / 2 * (rand() % 2),
					&target));
			else
				target.entity.push_back(new AttackSpeedVendor((float) window.getSize().y / 2 / ROWS_NUMBER,
					(float) window.getSize().y / 2 / ROWS_NUMBER,
					target.getCell(x, y)->getX() + target.getCellWidth() / 2 * (rand() % 2),
					target.getCell(x, y)->getY() + target.getCellHeight() / 2 * (rand() % 2),
					&target));
			target.board[x][y]->setFilled(true);
		}
		
}

void GameController::emplaceChests(Board& target)
{
	
			
			
				if (rand() % 7 == 0)
				{
					int k;
					int x = 0;
					int y = 1;

					k = rand() % ((ROWS_NUMBER - 2) * (COLUMNS_NUMBER - 2)) + 1;

					while (k > 0)
					{

						x++;
						if (x >= COLUMNS_NUMBER - 2)
						{
							y++;
							x = 1;
						}
						if (y >= ROWS_NUMBER - 2)
							y = 1;
						if (!target.getCell(x, y)->isCellTangible() && !target.getCell(x, y)->isFilled())
						{
							k--;

						}

					}

					target.entity.push_back(new Chest((float) window.getSize().y / 2 / ROWS_NUMBER,
						(float) window.getSize().y / 2 / ROWS_NUMBER,
						target.getCell(x, y)->getX() + target.getCellWidth() / 4,
						target.getCell(x, y)->getY() + target.getCellHeight() / 4,
						Color(255, 204, 0),
						Color(176, 46, 0),
						&target));
					target.board[x][y]->setFilled(true);
				}
			
		
}

void GameController::startGameLoop()
{
	
	srand((unsigned int) time(NULL));
	window.create(sf::VideoMode(1920, 1080), "Wizardly", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(55);


	font = new Font();
	font->loadFromFile("arial.ttf");

	for (int i = 0; i < BOARD_NUMBER; i++)
		for (int j = 0; j < BOARD_NUMBER; j++)
		{
			boardComplex[i][j] = Board(1, (float) window.getSize().x, (float) window.getSize().y);
		}

	while (window.isOpen())
	{

		prepareNewGame();
		while (player.isAlive() && !didPlayerWin && window.isOpen())
		{
			boardComplex[xboard][yboard].update();

			window.draw(boardComplex[xboard][yboard]);
			for (size_t i = 0; i < playerSpeed.size(); i++)
				window.draw(playerSpeed[i]);
			for (size_t i = 0; i < playerStrength.size(); i++)
				window.draw(playerStrength[i]);
			for (size_t i = 0; i < playerGold.size(); i++)
				window.draw(playerGold[i]);
			window.draw(playerSpeedText);
			window.draw(playerStrengthText);
			window.draw(playerGoldText);

			window.display();

			checkInput();
		}

		if (!window.isOpen())
			return;
		boardComplex[xboard][yboard].update();
		window.draw(boardComplex[xboard][yboard]);
		displayEndMessage();

		while (true)
		{
			if (window.pollEvent(msg) && (msg.type == Event::KeyPressed))
			{
				if (msg.key.code == Keyboard::Escape)
				{
					window.close();
					return;
				}
				if (msg.key.code == Keyboard::Enter)
				{
					break;
				}
			}

		}
	}
	player.clearPlayer();
	delete font;

}

sf::Font* GameController::getFont()
{
	return font;
}

Player* GameController::getPlayer()
{
	return &player;
}

void GameController::winGame()
{
	didPlayerWin = true;
}

void GameController::checkMovementInput()
{
	if (!(Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Down)))
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (!manualMode)
				player.setDir(1);

			player.move(1, player.getStrength());
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (!manualMode)
				player.setDir(3);

			player.move(3, player.getStrength());
		}
	if (!(Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Right)))
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (!manualMode)
				player.setDir(2);

			player.move(2, player.getStrength());
		}
		else  if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (!manualMode)
				player.setDir(4);

			player.move(4, player.getStrength());
		}
}

void GameController::checkSpecialInput()
{
	while (window.pollEvent(msg))
	{
		if (msg.type == Event::Closed)
		{
			window.close();
		}
		if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::Escape)
		{
			window.close();
		}
		if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::E)
		{
			player.interact();
		}
		if (manualMode)
			if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::W)
			{

				player.setDir(player.getDirection() - 1);
				if (player.getDirection() < 1)
					player.setDir(4);
				player.setAppearance();
			}
		if (manualMode)
			if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::S)
			{
				player.setDir(player.getDirection() + 1);
				if (player.getDirection() > 4)
					player.setDir(1);
				player.setAppearance();
			}
		if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::D)
		{
			player.nextWeapon();
		}
		if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::A)
		{
			player.previousWeapon();
		}
		if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::Z)
		{
			manualMode = manualMode ? 0 : 1;
		}
		if (msg.type == Event::KeyPressed && msg.key.code == Keyboard::Tab)
		{
			mapComplex.show(window);
		}
		if (msg.type == Event::Resized)
		{
			window.display();
		}

	}
}

void GameController::checkInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		player.attack();
	}
	checkMovementInput();
	checkSpecialInput();
}

void GameController::displayEndMessage()
{
	RectangleShape back;
	back.setSize(Vector2f((float) window.getSize().x / 3, (float) window.getSize().y / 4));
	back.setFillColor(Color(70, 70, 70));
	back.setPosition((float) window.getSize().x / 3, (float) window.getSize().y / 8 * 3);
	window.draw(back);

	Text score = Text();
	Text outcome = Text();
	score.setFont(*font);
	outcome.setFont(*font);
	std::stringstream stream;
	std::string temp;
	stream << player.getPoints();
	stream >> temp;

	temp = "Score:" + temp;
	if (didPlayerWin)
	{
		outcome.setString("You win");
	}
	else
	{
		outcome.setString("Game over");
	}

	score.setString(temp);
	score.setCharacterSize(50);
	score.setPosition(window.getSize().x / 2 - score.getGlobalBounds().width / 2,
		window.getSize().y / 2 - score.getGlobalBounds().height / 2);
	window.draw(score);

	outcome.setCharacterSize(50);
	outcome.setPosition(window.getSize().x / 2 - outcome.getGlobalBounds().width / 2,
		window.getSize().y / 2 - outcome.getGlobalBounds().height / 2 - 50);
	window.draw(outcome);
	window.display();
}

void GameController::changeBoard(int x, int y)
{
	boardComplex[xboard][yboard].timer = 0;
	boardComplex[xboard][yboard].projectiles.clear();
	boardComplex[xboard][yboard].entity.erase(boardComplex[xboard][yboard].entity.begin());
	yboard = (yboard + y + BOARD_NUMBER) % BOARD_NUMBER;
	xboard = (xboard + x + BOARD_NUMBER) % BOARD_NUMBER;
	mapComplex.maps[xboard][yboard].find();
	player.board = &boardComplex[xboard][yboard];
	boardComplex[xboard][yboard].entity.insert(boardComplex[xboard][yboard].entity.begin(), &player);
}

int GameController::getCurrentMapX()
{
	return xboard;
}

int GameController::getCurrentMapY()
{
	return yboard;
}

void GameController::updateStrength(int val)
{
	std::stringstream temp; temp << val;
	std::string temps; 
	temp >> temps;
	playerStrengthText.setString(temps);
}

void GameController::updateSpeed(int val)
{
	std::stringstream temp; temp << val;
	std::string temps;
	temp >> temps;
	playerSpeedText.setString(temps);
}

void GameController::updateGold(int val)
{
	std::stringstream temp;
	temp << val;
	std::string temps;
	temp >> temps;
	playerGoldText.setString(temps);
}
