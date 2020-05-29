#ifndef _Graphic_
#define _Graphic_

#include "LibrariesAndDefines.hpp"
#include "Option.hpp"

class Building;
class Bullet;
class Enemy;

class Graphic
{
	public :
		void showEndOfGame(bool win , Window& window);
		void letOut(Window& window);
		void drawBackGround(int lives, int money, int this_round, int total_round, Window& window);
		void showTextes(int lives, int money, int this_round, int total_round, Window& window);
		void drawPath(const std::vector<Point>& orginal_path, Window& window);
		void drawThings(const std::vector<Building*>& buildings, const std::vector<Enemy*>& enemies,const std::vector<Bullet*>& bullets, Window& window);
		void showOptions(Window& window);
		void showBuildingsType(Window& window);
		void showBuildCosts(Window& window);
		void showUpgradeCosts(Window& window);
		void showOptions(std::vector<Option> options, Window& window);
		void drawRing(Point center, int in_rad, int out_rad, Window& window);
		void letBegin(Window& window);
};

#endif