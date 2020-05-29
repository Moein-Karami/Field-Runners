#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Tool.hpp"

using namespace std;

const int SPEED[] = {GATTLING_BULLET_SPEED, MISILE_BULLET_SPEED,
	TESLA_BULLET_SPEED, GLUE_BULLET_SPEED};
const int RAD[] = {GATTLING_DAMAGE_RAD, MISILE_DAMAGE_RAD,
	TESLA_DAMAGE_RAD, GLUE_DAMAGE_RAD};
const vector<RGB> BULLET_COLOR = {GATTLING_BULLET_COLOR, MISILE_BULLET_COLOR,
	TESLA_BULLET_COLOR, GLUE_BULLET_COLOR};

Tool bullet_tool;

Bullet::Bullet(Point coordinates_, Enemy* target_,int bullet_type_)
	: Thing(coordinates_)
{
	target = target_;
	bullet_type = bullet_type_; 
	speed = SPEED[bullet_type];
	rad= RAD[bullet_type];
	bullet_color = BULLET_COLOR[bullet_type];
}


DamageBullet::DamageBullet(Point coordinates_, Enemy* target_, int bullet_type_, int damage_)
	: Bullet(coordinates_, target_, bullet_type_)	
{
	damage = damage_;
}

GlueBullet::GlueBullet(Point coordinates_, Enemy* target_, int bullet_type_, 
	int slow_percent_,int infection_time_)
	: Bullet(coordinates_, target_, bullet_type_)
{
	slow_percent = slow_percent_;
	infection_time = infection_time_;
}

bool Bullet::attack(const vector<Enemy*>& enemies)
{
	moveToTarget();
	if(bullet_tool.checkEqualityOfPoints(coordinates, target -> getCoordinates()))
	{
		explode(enemies);
		return true;
	}
	return false;
}

void Bullet::moveToTarget()
{
	Point destination = target -> getCoordinates();
	coordinates =bullet_tool.moveToDestination(coordinates, destination, speed);
}

void Bullet::explode(const vector<Enemy*>& enemies)
{
	if(rad == ZERO)
		hurt(target);
	else
		for(int i=ZERO; i < enemies.size(); i++)
			if(bullet_tool.getDistance(coordinates, enemies[i] -> getCoordinates()) <= rad)
				hurt(enemies[i]);
}

void DamageBullet::hurt(Enemy* enemy)
{
	if(cantHurt(enemy))
		return;
	enemy -> hurt(damage);
}

bool DamageBullet::cantHurt(Enemy* enemy)
{
	if(bullet_type == GATTLING_NUMBER && enemy -> isStubbornType() )
		return true;
	return false;
}

void GlueBullet::hurt(Enemy* enemy)
{
	if(cantHurt(enemy))
		return;
	enemy -> stuck(slow_percent, infection_time);
}

bool GlueBullet::cantHurt(Enemy* enemy)
{
	if(enemy -> isStubbornType() || enemy->isStuck())
		return true;
	return false;
}

void Bullet::draw(Window& window)
{
	window.fill_circle(coordinates, BULLET_RAD, bullet_color);
}