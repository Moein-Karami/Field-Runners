#ifndef _Enemy_
#define _Enemy_

#include "LibrariesAndDefines.hpp"
#include "Thing.hpp"

class Enemy : public Thing
{
	protected :
		int damage;
		double health;
		int speed;
		int point_of_path;
		int slow_percent;
		int last_glue_shot_time_remain;
		bool is_in_game;
		bool stubborn_type;
		double pixel_step;
		int price_situation;
		int price;
		int pic_size;
		int max_health;
		int pic_mode;
		int pic_steps;
		int die_mode;
		std::string name;
	public :
		Enemy(int enemy_type, int round, Point coordinate);
		bool isInGame();
		bool isStubbornType();
		void hurt(int damage);
		bool isStuck();
		void stuck(int slow_percent_, int infection_time);
		void keepMoving(const std::vector<Point>& path);
		int attack(const std::vector<Point>& path);
		void updatePic(Point start, Point end);
		double calculateSpeed();
		int loot();
		void draw(Window& window);
		bool isInDieMode();
		void updatePicDieMode();
		void drawLifeBar(Window& window);
		void makeDieNoise(Window& window);
		Point getCoordinates();
};

#endif