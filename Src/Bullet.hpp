#ifndef _Bullet_
#define _Bullet_

#include "LibrariesAndDefines.hpp"
#include "Thing.hpp"

class Enemy;

class Bullet : public Thing
{
	protected:
		Enemy* target;
		int speed;
		int rad;
		RGB bullet_color=WHITE;
		int bullet_type;
	public :
		Bullet(Point coordinates_, Enemy* target_,int bullet_type_);
		bool attack(const std::vector<Enemy*>& enemies);
		void moveToTarget();
		void explode(const std::vector<Enemy*>& enemies);
		virtual void hurt(Enemy* enemy) = ZERO ;
		void draw(Window& window);
};

class DamageBullet : public Bullet
{
	protected :
		int damage;
	public :
		DamageBullet(Point coordinates_, Enemy* target_, int bullet_type_, int damage);
		void hurt(Enemy* enemy);
		bool cantHurt(Enemy* enemy);
};

class GlueBullet : public Bullet
{
	protected :
		int slow_percent;
		int infection_time;
	public :
		GlueBullet(Point coordinates_, Enemy* target_, int bullet_type_, int slow_percent_, int infection_time_);
		void hurt(Enemy* enemy);
		bool cantHurt(Enemy* enemy);

};

#endif
