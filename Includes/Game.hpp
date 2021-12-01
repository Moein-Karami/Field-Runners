#ifndef _Game_
#define _Game_

#include "LibrariesAndDefines.hpp"
#include "Option.hpp"

class Building;
class Enemy;
class Bullet;
class Thing;

class Game
{
	protected :
		Window window=Window( WINDOW_WIDTH, WINDOW_HEIGHT, FIELD_RUNNERS);
		int lives;
		int money;
		std::vector<Point> path;
		std::vector<Building*> buildings;
		std::vector<Enemy*> enemies;
		std::vector<Bullet*> bullets;
		std::vector<Enemy*> coming_enemies;
		LL last_enemy_sent_time;
		Point chosen_point;
		std::vector<Point> orginal_path;
		std::vector<Option> options;
		int total_rounds;
		int round;
	public :
		Game(std::vector<std::vector<int>> data);
		void play(std::vector<std::vector<int>> data);
		void cleanMemory();
		bool playRound();
		void updateGame();
		void drawMap();
		void updateEnemies();
		void updateBullets();
		void updateBuildings();
		void checkEvents();
		void handleKeyPress(Event event);
		void buildBuilding(char building_type, Building* chosen_building);
		bool payForBuilding(char building_type);
		void deleteBuildingOfMap(Building* building);
		bool isInPath(Point point);
		Building* findBuildingByCoordinates(Point coordinates);
		bool isRoundOver();
		void sendNewEnemy();
		bool checkSendEnemyPossibility();
		void generateComingEnemies(std::vector<int> data);
		void breakTime(int remain_time);
		void cleanOptions();
		void handleLeftClick(Event event);
		bool chooseOption();
		void handleOptionChoose();
		void fixOptions();
		void addUpgradeOption();
		void doOptionOrder(char equal_key);

};

#endif