#include "Settings.h"
#include "Map.h"
#include <SFML\Graphics.hpp>
#include<iostream>
#include "GameController.h"

void Map::setAppearance()
{
	
	for (int i = -MAP_DIVISION / 2 - 1; i <= MAP_DIVISION / 2 + 1; i++)
		for (int j = - MAP_DIVISION / 2 - 1 ; j <= MAP_DIVISION / 2 + 1; j++)
		{		
			int currentBoardX = (xmiddle + i + BOARD_NUMBER) % BOARD_NUMBER;
			int currentBoardY = (ymiddle + j + BOARD_NUMBER) % BOARD_NUMBER;
			int newX = maps[xmiddle][ymiddle].getLocationX() + i * maps[xmiddle][ymiddle].getWidth();
			int newY = maps[xmiddle][ymiddle].getLocationY() + j * maps[xmiddle][ymiddle].getHeight();
			if (newX == maps[currentBoardX][currentBoardY].getLocationX() && newY == maps[currentBoardX][currentBoardY].getLocationY())
				continue;

			maps[currentBoardX][currentBoardY].setLocationX(maps[xmiddle][ymiddle].getLocationX() + i * maps[xmiddle][ymiddle].getWidth());

			maps[currentBoardX][currentBoardY].setLocationY(maps[xmiddle][ymiddle].getLocationY() + j * maps[xmiddle][ymiddle].getHeight());

			maps[currentBoardX][currentBoardY].setAppearance();
	}
}
void Map::show(sf::RenderWindow &window)
{
	sf::Vector2i pMouse;
	sf::Event msg;
	xmiddle = GameController::getCurrentMapX();
	ymiddle = GameController::getCurrentMapY();
	maps[xmiddle][ymiddle].setMainStatus();
	maps[xmiddle][ymiddle].setLocationX(window.getSize().x / 2 - maps[xmiddle][ymiddle].getWidth() / 2);
	maps[xmiddle][ymiddle].setLocationY(window.getSize().y / 2 - maps[xmiddle][ymiddle].getHeight() / 2);
	setAppearance();
	while (window.isOpen())
	{
		
		for (int i = 0; i < MAP_DIVISION + 2; i++)
			for (int j = 0; j < MAP_DIVISION + 2; j++)
			{
				int currentBoardX = (xmiddle + i - MAP_DIVISION / 2 - 1 + BOARD_NUMBER) % BOARD_NUMBER;
				int currentBoardY = (ymiddle + j - MAP_DIVISION / 2 - 1 + BOARD_NUMBER) % BOARD_NUMBER;
				maps[currentBoardX][currentBoardY].setAppearance();
				window.draw(maps[currentBoardX][currentBoardY]);
				
			}
		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			
				move(3);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
				move(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
				move(2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
				move(4);
		}
		while (window.pollEvent(msg))
		{
			if (msg.type == sf::Event::KeyPressed && msg.key.code == sf::Keyboard::Tab)
			{
				maps[GameController::getCurrentMapX()][GameController::getCurrentMapY()].removeMainStatus();
				return;

			}
			if (msg.type == sf::Event::Closed)
			{
				window.close();
			}
			if (msg.type == sf::Event::KeyPressed && msg.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
	}
}
void Map::move(int move)
{
	switch (move)
	{
	case 1:
		
		maps[xmiddle][ymiddle].changeLocationY(-4);
		setAppearance();
		if (maps[xmiddle][(ymiddle - MAP_DIVISION / 2 - 1 + BOARD_NUMBER) % BOARD_NUMBER].getLocationY() + maps[0][0].getHeight() < 0)
		{
			ymiddle = (ymiddle + 1) % BOARD_NUMBER;
		}
		break;
	case 2:
		maps[xmiddle][ymiddle].changeLocationX(4);
		setAppearance();
		if (maps[(xmiddle + MAP_DIVISION / 2 + 1 + BOARD_NUMBER) % BOARD_NUMBER][ymiddle].getLocationX() > maps[0][0].getWidth() * MAP_DIVISION)
		{
			xmiddle = (xmiddle - 1 + BOARD_NUMBER) % BOARD_NUMBER;
		}
		break;
	case 3:
		maps[xmiddle][ymiddle].changeLocationY(4);
		setAppearance();
		if (maps[xmiddle][(ymiddle + MAP_DIVISION / 2 + 1 + BOARD_NUMBER) % BOARD_NUMBER].getLocationY() > maps[0][0].getHeight() * MAP_DIVISION)
		{
			ymiddle = (ymiddle - 1 + BOARD_NUMBER) % BOARD_NUMBER;
		}
		break;
	case 4:
		maps[xmiddle][ymiddle].changeLocationX(-4);
		setAppearance();
		if (maps[(xmiddle - MAP_DIVISION / 2 - 1 + BOARD_NUMBER) % BOARD_NUMBER][ymiddle].getLocationX() + maps[0][0].getWidth() < 0)
		{
			xmiddle = (xmiddle + 1) % BOARD_NUMBER;
		}
		break;
	}
	setAppearance();
}