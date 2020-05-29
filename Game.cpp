#include "Game.hpp"
#include "Tool.hpp"
#include "Building.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Thing.hpp"
#include "Graphic.hpp"
#include <algorithm>
using namespace std;

Tool game_tool;
Graphic graphic;

const int BUILDING_COSTS[]={GATTLING_BUILD_COST, MISILE_BUILD_COST,
		TESLA_BUILD_COST, GLUE_BUILD_COST};

Game::Game(vector<vector<int>> data)
{
	lives = BASE_HEALTH;
	money = BASE_MONEY;
	path = game_tool.buildPixelPath(data[PATH_IN_DATA]);
	orginal_path = game_tool.makePairVectorData(data[PATH_IN_DATA]);
	orginal_path = game_tool.completePath(orginal_path);
	last_enemy_sent_time = ZERO ;
	chosen_point = OUT_POINT;
	total_rounds = data.size() - ONE;
}

void Game::play(vector<vector<int>> data)
{
	graphic.letBegin(window);
	bool is_alive=true;
	window.play_music(BACKGROUND_MUSIC);
	for(round = ONE; round <= total_rounds; round++)
	{
		breakTime(TIME_OUT);
		generateComingEnemies(data[round]);
		window.play_sound_effect(RUN_MUSIC);
		is_alive = playRound();
		if(is_alive == false)
			break;
	}
	round = total_rounds;
	breakTime(THOUSAND);
	graphic.showEndOfGame(is_alive, window);
	cleanMemory();
}

void Game::breakTime(int remain_time)
{
	while(remain_time > ZERO)
	{
		remain_time-=DELAY_TIME;
		updateGame();
		drawMap();
		delay(DELAY_TIME);
	}
}

void Game::cleanMemory()
{
	for(int i = ZERO; i < buildings.size(); i++)
		delete buildings[i];
	for(int i = ZERO; i < enemies.size(); i++)
		delete enemies[i];
	for(int i = ZERO; i < bullets.size(); i++)
		delete bullets[i];
}

bool Game::playRound()
{
	while(isRoundOver() == false)
	{
		updateGame();
		drawMap();
		if(lives <= ZERO)
			break;
		delay(DELAY_TIME);
	}
	return lives > ZERO;
}

void Game::updateGame()
{
	sendNewEnemy();
	checkEvents();
	updateBuildings();
	updateBullets();
	updateEnemies();
}

void Game::drawMap()
{
	graphic.drawBackGround(lives, money, round, total_rounds, window);
	graphic.drawPath(orginal_path, window);
	graphic.drawThings(buildings, enemies, bullets, window);
	graphic.showOptions(options, window);
	window.update_screen();
}

void Game::updateEnemies()
{
	for(int i = ZERO; i < enemies.size(); i++)
	{
		enemies[i] -> makeDieNoise(window);
		money += enemies[i] -> loot();
		if(enemies[i] -> isInDieMode())
			enemies[i] -> updatePicDieMode();
		if(enemies[i] ->  isInGame() == false)
			continue;
		enemies[i] -> keepMoving (path);
		lives -= enemies[i] -> attack(path);
	}
}

void Game::updateBullets()
{
	for(int i = ZERO; i < bullets.size(); i++)
	{
		if(bullets[i] -> attack(enemies))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void Game::updateBuildings()
{
	for(int i=ZERO; i<buildings.size(); i++)
	{
		buildings[i] -> updatePic(enemies);
		if(buildings[i] -> canShot(enemies))
			bullets.push_back(buildings[i] -> shot(enemies, window)); 
	}
}

void Game::checkEvents()
{
	Event event;
	while(window.has_pending_event())
	{
		event=window.poll_for_event();
		if(event.get_type() == Event::QUIT)
			abort();
		else if(event.get_type() == Event::LCLICK)
			handleLeftClick(event);
		else if(event.get_type() == Event::KEY_PRESS)
			handleKeyPress(event);
		else if(event.get_type() == Event::RCLICK)
			cleanOptions();
	}
}

void Game::cleanOptions()
{
	chosen_point = OUT_POINT;
	options.clear();
}

void Game::handleLeftClick(Event event)
{
	chosen_point = event.get_mouse_position();
	if(chooseOption())
		handleOptionChoose();
	else
		fixOptions();
}

bool Game::chooseOption()
{
	for(int i=ZERO; i < options.size(); i++)
		if(game_tool.getDistance(chosen_point, options[i].getCoordinates()) < SQUARE_LENGTH / TWO)
			return true;
	return false;
}

void Game::handleOptionChoose()
{
	for(int i=ZERO; i < options.size(); i++)
	{
		if(game_tool.getDistance(chosen_point, options[i].getCoordinates()) < SQUARE_LENGTH / TWO)
		{
			chosen_point = options[i].getBasePoint();
			doOptionOrder(options[i].getEqualKey());
			cleanOptions();
			return;
		}
	}
}

void Game::doOptionOrder(char equal_key)
{
	Building* chosen_building = findBuildingByCoordinates(chosen_point);
	if(equal_key != UPGRADE_KEY)
		buildBuilding(equal_key, chosen_building);
	else
		money -= chosen_building -> upgrade(money);
}

void Game::fixOptions()
{
	Point tmp = chosen_point;
	cleanOptions();
	chosen_point = game_tool.fixChosenPoint(tmp); 
	if(game_tool.checkEqualityOfPoints(chosen_point, OUT_POINT) || 
		isInPath (chosen_point))
	{
		cleanOptions();
		return ;
	}
	for(int i=ZERO; i < FOUR; i++)
		if(money >= BUILDING_COSTS[i])
			options.push_back(Option(i, chosen_point));
	addUpgradeOption();
}

void Game::addUpgradeOption()
{
	Building* building=findBuildingByCoordinates(chosen_point);
	if(building == NULL)
		return ;
	if (building -> cantUpgrade(money))
		return ;
	options.push_back(Option(FOUR, chosen_point));
}

void Game::handleKeyPress(Event event)
{
	chosen_point = game_tool.fixChosenPoint(chosen_point);
	if(game_tool.checkEqualityOfPoints(chosen_point, OUT_POINT) || isInPath(chosen_point))
		return ;
	Building* chosen_building = findBuildingByCoordinates(chosen_point);
	char key_pressed = event.get_pressed_key();
	if(key_pressed == UPGRADE_KEY && chosen_building != NULL)
		money -= chosen_building -> upgrade(money);
	else 
		buildBuilding(key_pressed, chosen_building);
	cleanOptions();
}

void Game::buildBuilding(char building_type, Building* chosen_building)
{
	if(chosen_building != NULL)
		deleteBuildingOfMap(chosen_building);
	Building* new_building;
	if(payForBuilding(building_type) == false)
		return;
	switch(building_type)
	{
		case GATTLING_KEY:
			new_building = new DamageBuilding(chosen_point, GATTLING_NUMBER);
			break;
		case MISILE_KEY:
			new_building = new DamageBuilding(chosen_point, MISILE_NUMBER);
			break;
		case TESLA_KEY:
			new_building = new DamageBuilding(chosen_point, TESLA_NUMBER);
			break;
		case GLUE_KEY:
			new_building = new GlueBuilding(chosen_point, GLUE_NUMBER);
			break;
		default :
			return;
	}
	buildings.push_back(new_building);
}

bool Game::payForBuilding(char building_type)
{
	switch(building_type)
	{
		case GATTLING_KEY:
			if(money < GATTLING_BUILD_COST)
				return false;
			else
				money -= GATTLING_BUILD_COST;
			break;
		case MISILE_KEY:
			if(money < MISILE_BUILD_COST)
				return false;
			else
				money -= MISILE_BUILD_COST;
			break;
		case TESLA_KEY:
			if(money < TESLA_BUILD_COST)
				return false;
			else
				money -= TESLA_BUILD_COST;
			break;
		case GLUE_KEY:
			if(money < GLUE_BUILD_COST)
				return false;
			else
				money -= GLUE_BUILD_COST;
			break;
		default :
			break;
	}
	return true;
}

void Game::deleteBuildingOfMap(Building* building)
{
	for(int i=ZERO; i < buildings.size(); i++)
		if(buildings[i] == building)
			buildings.erase(buildings.begin()+i);
	delete building;
}


bool Game:: isInPath(Point point)
{
	for(int i = ZERO; i < path.size(); i++)
		if(game_tool.checkEqualityOfPoints(point, path[i]))
			return true;
	return false;
}

Building* Game::findBuildingByCoordinates(Point coordinates)
{
	for(int i = ZERO; i < buildings.size(); i++)
		if(game_tool.checkEqualityOfPoints(buildings[i] -> getCoordinates(), coordinates))
			return buildings[i];
	return NULL;
}

bool Game::isRoundOver()
{
	if(coming_enemies.size())
		return false;
	for(int i=ZERO; i<enemies.size(); i++)
		if(enemies[i] -> isInGame())
			return false;
	return true;
}


void Game::sendNewEnemy()
{
	LL now=GET_TIME;
	if(checkSendEnemyPossibility() == false)
		return ;
	enemies.push_back(coming_enemies[ZERO]);
	last_enemy_sent_time = now;
	coming_enemies.erase(coming_enemies.begin());
}

bool Game::checkSendEnemyPossibility()
{
	LL now=GET_TIME;
	if(now - last_enemy_sent_time < SEND_ENEMY_PERIOD)
		return false;
	if(coming_enemies.size() == ZERO)
		return false;
	return true;
}

void Game::generateComingEnemies(vector<int> data)
{
	for(int enemy_type = ZERO; enemy_type < data.size(); enemy_type++)
		for(int i = ZERO; i < data[enemy_type]; i++)
			coming_enemies.push_back(new Enemy(enemy_type, round, path[ZERO]));
	random_shuffle(coming_enemies.begin(), coming_enemies.end());
}