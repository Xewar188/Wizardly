#pragma once
#include "Board.h"
#include "Player.h"
#include "Settings.h"

#include <stdlib.h>
#include <time.h>
#include <SFML\Window.hpp>

class Map;
class GameController {
	static Board boardComplex[BOARD_NUMBER][BOARD_NUMBER];//wszystkie mapy 
	static sf::RenderWindow window;

	static Event msg;
	static Player player;
	static Map mapComplex;
	static int xboard, yboard;
	static std::vector<sf::RectangleShape> playerSpeed;
	static std::vector<sf::RectangleShape> playerStrength;
	static std::vector<sf::RectangleShape> playerGold;
	static sf::Text playerGoldText;
	static sf::Text playerSpeedText;
	static sf::Text playerStrengthText;
	static sf::Font* font;
	static bool didPlayerWin;
	static bool manualMode;
	static void prepareNewGame();
	static void checkMovementInput();
	static void checkSpecialInput();
	static void checkInput();
	static void displayEndMessage();
	static void prepareBoards();

	static void createBasicBoards();
	static void createStatIcons();
	static void openPassages();
	static void emplaceShrines(Board& target);
	static void emplaceArtifacts();
	static void emplaceMages(Board& target);
	static void emplaceWarriors(Board& target);
	static void emplaceHealing(Board& target);
	static void emplaceVendors(Board& target);
	static void emplaceChests(Board& target);
public:
	
	static void startGameLoop();
	static sf::Font* getFont();
	static Player* getPlayer();
	static void winGame();
	static void changeBoard(int x, int y);
	static int getCurrentMapX();
	static int getCurrentMapY();
	static void updateStrength(int val);
	static void updateSpeed(int val);
	static void updateGold(int val);
};

