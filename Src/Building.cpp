#include "Building.hpp"
#include "Tool.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
using namespace std;

const vector<vector<string>> BUILDINGS_IMG_PATH={
	{"", GATTLING1_IMG_PATH, GATTLING2_IMG_PATH, GATTLING3_IMG_PATH},
	{"", MISILE1_IMG_PATH, MISILE2_IMG_PATH, MISILE3_IMG_PATH},
	{"", TESLA1_IMG_PATH, TESLA2_IMG_PATH, TESLA3_IMG_PATH},
	{"", GLUE1_IMG_PATH, GLUE2_IMG_PATH, GLUE3_IMG_PATH}
};
const int SHOT_PERIOD[] = {GATTLING_SHOT_PERIOD, MISILE_SHOT_PERIOD,
	TESLA_SHOT_PERIOD, GLUE_SHOT_PERIOD};
const int UPGRADE_COST[] = {GATTLING_UPGRADE_COST, MISILE_UPGRADE_COST,
	TESLA_UPGRADE_COST, GLUE_UPGRADE_COST};
const int UPGRADE_DAMAGE[] = {GATTLING_UPGRADE_DAMAGE, MISILE_UPGRADE_DAMAGE,TESLA_UPGRADE_DAMAGE};
const int BASIC_SHOT_DAMAGE[] = {GATTLING_BASE_DAMAGE, MISILE_BASE_DAMAGE, TESLA_BASE_DAMAGE};
const string NAMES[]={GATTLING, MISILE, TESLA, GLUE};
Tool building_tool;

Building::Building(Point chosen_point, int building_type_)
	: Thing(chosen_point, BUILDINGS_IMG_PATH[building_type_][ONE])
{
	building_type = building_type_;
	target = NULL;
	shot_period = SHOT_PERIOD[building_type_];
	upgrade_cost = UPGRADE_COST[building_type_];
	setImgPathCollection();
	level = ONE ;
	last_shot = ZERO ;
	name = NAMES[building_type];
}

void Building::setImgPathCollection()
{
	for(int i=ZERO; i < BUILDINGS_IMG_PATH[building_type].size(); i++)
		img_path_collection.push_back(BUILDINGS_IMG_PATH[building_type][i]);
}

DamageBuilding::DamageBuilding(Point chosen_point, int building_type_)
	: Building(chosen_point,building_type_)
{
	shot_damage = BASIC_SHOT_DAMAGE[building_type_];
	upgrade_damage = UPGRADE_DAMAGE[building_type_];
}

GlueBuilding::GlueBuilding(Point chosen_point, int building_type_)
	: Building(chosen_point, building_type_)
{
	shot_slow_percent = GLUE_BASE_PERCENT;
	upgrade_slow_percent = GLUE_UPGRADE_PERCENT;
	infection_time = GLUE_INFECTION_TIME;
	upgrade_infection_time = GLUE_UPGRADE_INFECTION_TIME;
}

int DamageBuilding::upgrade(int money)
{
	if(money < upgrade_cost || level == MAX_LEVEL)
		return ZERO;
	level++;
	img_path = img_path_collection[level];
	shot_damage += upgrade_damage;
	return upgrade_cost;
}

int GlueBuilding::upgrade(int money)
{
	if(money < upgrade_cost || level == MAX_LEVEL)
		return ZERO;
	level++;
	img_path = img_path_collection[level];
	shot_slow_percent += upgrade_slow_percent;
	infection_time += upgrade_infection_time;
	return upgrade_cost;
}

bool Building::canShot(const vector<Enemy*>& enemies)
{
	LL now = GET_TIME;
	if(now - last_shot < shot_period )
		return false;
	if(checkValidTargetExists(enemies) == false)
		return false;
	return true;
}

Bullet* DamageBuilding::shot(const vector<Enemy*>& enemies, Window& window)
{
	window.play_sound_effect(ASSETS + name + SOUND);
	last_shot = GET_TIME;
	return new DamageBullet(coordinates, target, building_type, shot_damage);
}

Bullet* GlueBuilding::shot(const vector<Enemy*>& enemies, Window& window)
{
	window.play_sound_effect(ASSETS + name + SOUND);
	last_shot = GET_TIME;
	return new GlueBullet(coordinates, target,building_type,
		shot_slow_percent, infection_time);
}

bool Building::checkValidTargetExists(const vector<Enemy*>& enemies)
{
	checkTargetOut();
	if(target == NULL || target -> isInGame() == false)
		fixTarget(enemies);
	if(target == NULL)
		return false;
	return true;
}

void Building::checkTargetOut()
{
	if(target==NULL)
		return ;
	if(building_tool.getDistance(coordinates, target->getCoordinates()) > SHOOTING_RANGE)
		target=NULL;
}

void Building::fixTarget(const vector<Enemy*>& enemies)
{
	target = NULL;
	int mini_distance=INF;
	for(int i = ZERO; i < enemies.size(); i++)
	{
		if(enemies[i] -> isInGame() == false)
			continue;
		int distance=building_tool.getDistance(coordinates, enemies[i] -> getCoordinates());
		if(distance < mini_distance)
		{
			mini_distance = distance;
			target = enemies[i];
		}
	}
	if(mini_distance > SHOOTING_RANGE )
		target =NULL;
}

void Building::updatePic(const vector<Enemy*>& enemies)
{
	checkValidTargetExists(enemies);
	if(target == NULL || building_type == TESLA_NUMBER)
	{
		changeShotPic();
		return ;
	}
	Point target_coordinates = target -> getCoordinates();
	double rad_angle = atan2(coordinates.y - target_coordinates.y, 
		target_coordinates.x - coordinates.x);
	double angle = STRAIT_ANGLE * rad_angle / PI ;
	if(angle < ZERO)
		angle+=COMPLETE_ANGLE;
	if(angle > RIGHT_ANGLE && angle < REFLEX_ANGLE)
		reverse = true;
	else
		reverse = false;
	img_path = BUILDINGS;
	img_path += name; 
	img_path += to_string(level);
	img_path += to_string(getNumberOfAngle(angle));
	if(name == GATTLING && GET_TIME - last_shot <= HUNDRED)
		img_path+=SHOT;
	img_path+=PNG;
}

void Building::changeShotPic()
{
	int index = img_path.find(SHOT);
	if(index >= ZERO )
		img_path.erase(index, FOUR);
}

bool Building::cantUpgrade(int money)
{
	return ((upgrade_cost > money) || (level == MAX_LEVEL));
}

int Building::getNumberOfAngle(double angle)
{
	angle = fixAngle(angle);
	getchar();
	if(angle <= RIGHT_ANGLE)
	{
		if(angle >= RIGHT_ANGLE - ANGLE_DIFFERENCE)
			return ZERO;
		else if(angle >= RIGHT_ANGLE - THREE * ANGLE_DIFFERENCE)
			return ONE;
		else 
			return TWO;
	}
	else
	{
		if(angle >= COMPLETE_ANGLE - ANGLE_DIFFERENCE)
			return TWO;
		else if(angle >= COMPLETE_ANGLE - THREE * ANGLE_DIFFERENCE)
			return THREE;
		else
			return FOUR;
	}
}

double Building::fixAngle(double angle)
{
	if(angle > RIGHT_ANGLE && angle <= STRAIT_ANGLE)
		return STRAIT_ANGLE - angle;
	if(angle > STRAIT_ANGLE && angle <= REFLEX_ANGLE )
		return angle = angle +TWO * (REFLEX_ANGLE - angle);
	return angle;
}

Point Building::getCoordinates()
{
	return coordinates;
}