#include "Enemy.hpp"

using namespace std;

const double BASIC_HEALTHS[] = {RUNNER_BASE_HEALTH, STUBBORN_BASE_HEALTH,
		SUPER_TROOPER_BASE_HEALTH, SCRAMBLER_BASE_HEALTH};
const int BASIC_DAMAGES[] = {RUNNER_DAMAGE, STUBBORN_DAMAGE,
		SUPER_TROOPER_DAMAGE, SCRAMBLER_DAMAGE};
const int BASIC_SPEEDS[] = {RUNNER_SPEED, STUBBORN_SPEED,
		SUPER_TROOPER_SPEED, SCRAMBLER_SPEED};
const string IMG_PATH[] = {RUNNER_IMG_PATH, STUBBORN_IMG_PATH,
		SUPER_TROOPER_IMG_PATH,  SCRAMBLER_IMG_PATH};
const int PRICES[] = {RUNNER_PRICE, STUBBORN_PRICE, SUPER_TROOPER_PRICE,
	SCRAMBLER_PRICE};
const int PIC_SIZES[] = {RUNNER_PIC_SIZE, STUBBORN_PIC_SIZE,
	SUPER_TROOPER_PIC_SIZE, SCRAMBLER_PIC_SIZE};
const string NAMES[] ={RUNNER, STUBBORN, SUPER_TROOPER, SCRAMBLER};

Enemy::Enemy(int enemy_type, int round, Point coordinate)
	: Thing(coordinate, IMG_PATH[enemy_type])
{
	damage = BASIC_DAMAGES[enemy_type];
	health = (ZERO_POINT_NINE + ZERO_POINT_ONE * round ) * 
			BASIC_HEALTHS[enemy_type];
	max_health = health ;
	speed = BASIC_SPEEDS[enemy_type];
	point_of_path = ZERO;
	slow_percent = ZERO;
	last_glue_shot_time_remain = ZERO;
	is_in_game = true;
	stubborn_type = (enemy_type == STUBBORN_NUMBER);
	pixel_step = ZERO;
	price_situation = ALIVE;
	price = PRICES[enemy_type];
	pic_size = PIC_SIZES[enemy_type];
	name = NAMES[enemy_type];
	pic_mode = ZERO;
	pic_steps = ZERO;
	die_mode = ZERO;
}

bool Enemy::isInGame()
{
	return is_in_game;
}

bool Enemy::isStubbornType()
{
	return stubborn_type;
}

void Enemy::hurt(int damage)
{
	health -= damage;
	if(health < ZERO)
	{
		is_in_game= false;
		if(price_situation == ALIVE)
		{
			die_mode = FOUR * HUNDRED - ONE;
			price_situation = SHOULD_LOOT;
		}
	}
}

bool Enemy::isStuck()
{
	return last_glue_shot_time_remain > ZERO ;
}

void Enemy::stuck(int slow_percent_, int infection_time)
{
	last_glue_shot_time_remain = infection_time;
	slow_percent = slow_percent_;
}

void Enemy:: keepMoving(const vector<Point>& path)
{
	double current_speed = calculateSpeed();
	Point last_coordinates = coordinates;
	pixel_step += current_speed * (double) DELAY_TIME / THOUSAND ;
	point_of_path += (int) pixel_step;
	pixel_step -= (int) pixel_step;
	last_glue_shot_time_remain -= DELAY_TIME;
	if(point_of_path >= path.size())
		point_of_path = path.size() - ONE;
	coordinates = path[point_of_path];
	updatePic(last_coordinates, coordinates);
}

void Enemy::updatePic(Point start, Point end)
{
	if(die_mode > ZERO)
		updatePicDieMode();
	if(start.x == end.x && start.y == end.y)
		return ;
	img_path = ENEMIES + name;
	reverse = false;
	if(start.y < end.y)
		img_path+=DOWN;
	else if(start.y > end.y )
		img_path += UP;
	else if(start.x != end.x)
		img_path += RIGHT;
	if(start.x > end.x)
		reverse = true;
	pic_steps ++;
	if(pic_steps == CHANGE_PIC_FRAME)
	{
		pic_mode = (pic_mode+1) % PIC_MODES;
		pic_steps = ZERO;
	}
	img_path += to_string(pic_mode);
	img_path += PNG;
}

int Enemy::attack(const vector<Point>& path)
{
	if(point_of_path == path.size() - ONE)
	{
		is_in_game = false;
		coordinates = path.back();
		return damage;
	}
	return ZERO ;
}

double Enemy:: calculateSpeed()
{
	if(last_glue_shot_time_remain <= ZERO )
		return speed;
	return (double)speed * (double)(HUNDRED-slow_percent) / (double)HUNDRED;
}

int Enemy::loot()
{
	if(price_situation == SHOULD_LOOT )
	{
		price_situation = LOOTED;
		return price;
	}
	return ZERO;
}

void Enemy::draw(Window& window)
{
	if(die_mode <= ZERO)
		drawLifeBar(window);
	Rectangle dest_rect(coordinates.x - pic_size / TWO, coordinates.y - pic_size / TWO,
		pic_size , pic_size );
	window.draw_img(img_path, dest_rect, NULL_RECT, ZERO, reverse, false);
}

void Enemy::drawLifeBar(Window& window)
{
	int green_rect_length= pic_size * health / max_health;
	int red_rect_length = pic_size - green_rect_length ;
	Rectangle green_rect(coordinates.x - pic_size / TWO, coordinates.y - pic_size / TWO - FIVE,
		green_rect_length , FIVE);
	Rectangle red_rect(coordinates.x - pic_size / TWO + green_rect_length, coordinates.y - pic_size / TWO - FIVE,
		red_rect_length , FIVE);
	window.fill_rect(green_rect, GREEN);
	window.fill_rect(red_rect, RED);
}

bool Enemy::isInDieMode()
{
	return (die_mode > ZERO);
}

void Enemy::updatePicDieMode()
{
	img_path = ENEMIES + name + DIE + to_string(THREE - (int)(die_mode/HUNDRED)) + PNG;
	die_mode -= DELAY_TIME;
}

void Enemy::makeDieNoise(Window& window)
{
	if(price_situation == SHOULD_LOOT)
		window.play_sound_effect(ASSETS+name+DIE+MP3);
}

Point Enemy::getCoordinates()
{
	return coordinates;
}