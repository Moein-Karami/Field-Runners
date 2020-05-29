#ifndef _Building_
#define _Building_

#include "LibrariesAndDefines.hpp"
#include "Thing.hpp"

class Enemy;
class Bullet;

class Building : public Thing
{
	protected :
		Enemy* target;
		int shot_period;
		int level;
		int upgrade_cost;
		std::vector<std::string> img_path_collection;
		LL last_shot;
		int building_type;
		std::string name;
	public :
		virtual int upgrade(int money) = ZERO ;
		Point getCoordinates();
		Building(Point chosen_point, int building_type_);
		bool canShot(const std::vector<Enemy*>& enemies);
		virtual Bullet* shot(const std::vector<Enemy*>& enemies, Window& window) = ZERO;
		bool checkValidTargetExists(const std::vector<Enemy*>& enemies);
		void fixTarget(const std::vector<Enemy*>& enemies);
		void setImgPathCollection();
		void checkTargetOut();
		void updatePic(const std::vector<Enemy*>& enemies);
		int getNumberOfAngle(double angle);
		double fixAngle(double angle);
		void changeShotPic();
		bool cantUpgrade(int money);
};

class DamageBuilding : public Building
{
	protected :
		int shot_damage;
		int upgrade_damage;
	public :
		int upgrade(int money);
		DamageBuilding(Point chosen_point, int building_type_);
		Bullet* shot(const std::vector<Enemy*>& enemies, Window& window);
};

class GlueBuilding : public Building
{
	protected :
		int shot_slow_percent;
		int upgrade_slow_percent;
		int infection_time;
		int upgrade_infection_time;
	public :
		int upgrade(int money);
		GlueBuilding(Point chosen_point, int building_type_);
		Bullet* shot(const std::vector<Enemy*>& enemies, Window& window);

};

#endif