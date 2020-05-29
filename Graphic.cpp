#include "Graphic.hpp"
#include "Enemy.hpp"
#include "Building.hpp"
#include "Bullet.hpp"
#include "Thing.hpp"
#include "Tool.hpp"

using namespace std;

Tool graphic_tool;

void Graphic::showEndOfGame(bool win , Window& window)
{
	window.stop_music();
	if(win)
	{
		window.play_sound_effect(WIN_MUSIC);
		window.show_text(WIN, WIN_MSG_POINT, GREEN, FONT_PATH, END_MSG_SIZE);
	}
	else
	{
		window.play_sound_effect(LOST_MUSIC);
		window.show_text(LOOSE, LOOSE_MSG_POINT, RED, FONT_PATH, END_MSG_SIZE);
	}
	window.update_screen();
	letOut(window);
}

void Graphic::letOut(Window& window)
{
	Event event;
	do
	{
		event = window.poll_for_event();
		delay(DELAY_TIME);
		if(event.get_type() == Event::QUIT)
			abort();
	}while(event.get_type()!=Event::KEY_PRESS);
}

void Graphic::drawBackGround(int lives, int money, int this_round, int total_round, Window& window)
{
	window.clear();
	window.draw_img(BACKGROUND_IMG_PATH, NULL_RECT, NULL_RECT, ZERO, false, false);
	showTextes(lives, money, this_round, total_round, window);
	showOptions(window);
}

void Graphic::showTextes(int lives, int money, int this_round, int total_round, Window& window)
{
	window.show_text(LIVES + to_string(lives), LIVES_POINT, WHITE, FONT_PATH, TEXT_SIZE);
	window.show_text(MONEY + to_string(money), MONEY_POINT, WHITE, FONT_PATH, TEXT_SIZE);
	window.show_text(ROUND + to_string(this_round) + SLASH + to_string(total_round), Point(650,100),
	WHITE, FONT_PATH, TEXT_SIZE);
}

void Graphic::showOptions(Window& window)
{
	showBuildingsType(window);
	showBuildCosts(window);
	showUpgradeCosts(window);
}

void Graphic::showBuildingsType(Window& window)
{
	Point point = TOWER_TYPE_POINT;
	window.show_text(TOWER_TYPE_TEXT, point, WHITE, FONT_PATH, TEXT_SIZE);
	Rectangle dest_rect = TOWER_OPTION_RECT;
	window.draw_img(GATTLING_IMG, dest_rect, NULL_RECT, ZERO, false, false);
	dest_rect.x += PICS_DISTANCE;
	window.draw_img(MISILE_IMG, dest_rect, NULL_RECT, ZERO, false, false);
	dest_rect.x += PICS_DISTANCE + FIVE;
	window.draw_img(TESLA_IMG, dest_rect, NULL_RECT, ZERO, false, false);
	dest_rect.x += PICS_DISTANCE - FIVE;
	window.draw_img(GLUE_IMG, dest_rect, NULL_RECT, ZERO, false, false);
}

void Graphic::showBuildCosts(Window& window)
{
	Point point=BUILD_COST_POINT;
	window.show_text(BUILD_COST_TEXT, point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TWO * TEXTS_DISTANCE;
	window.show_text(to_string(GATTLING_BUILD_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TEXTS_DISTANCE;
	window.show_text(to_string(MISILE_BUILD_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TEXTS_DISTANCE;
	window.show_text(to_string(TESLA_BUILD_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TEXTS_DISTANCE;
	window.show_text(to_string(GLUE_BUILD_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
}

void Graphic::showUpgradeCosts(Window& window)
{
	Point point=UPGRADE_COST_POINT;
	window.show_text(UPGRADE_COST_TEXT, point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TWO * TEXTS_DISTANCE;
	window.show_text(to_string(GATTLING_UPGRADE_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TEXTS_DISTANCE;
	window.show_text(to_string(MISILE_UPGRADE_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TEXTS_DISTANCE;
	window.show_text(to_string(TESLA_UPGRADE_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
	point.x += TEXTS_DISTANCE;
	window.show_text(to_string(GLUE_UPGRADE_COST), point, WHITE, FONT_PATH, TEXT_SIZE);
}

void Graphic::drawPath(const vector<Point>& orginal_path, Window& window)
{
	for(int i = ZERO; i<orginal_path.size(); i++)
	{
		Point center=graphic_tool.getCenterOfSquare(orginal_path[i]);
		center.x -= SQUARE_LENGTH / TWO;
		center.y -= SQUARE_LENGTH / TWO;
		Rectangle rect(center, SQUARE_LENGTH, SQUARE_LENGTH);
		window.draw_rect(rect, GOLD, TWO);
	}
}

void Graphic::drawThings(const vector<Building*>& buildings, const vector<Enemy*>& enemies,
	const vector<Bullet*>& bullets, Window& window)
{
	for(int i = ZERO; i < buildings.size(); i++)
		buildings[i]->draw(window);
	for(int i = ZERO; i < enemies.size(); i++)
		if(enemies[i] -> isInGame() || enemies[i] -> isInDieMode())
			enemies[i]->draw(window);
	for(int i = ZERO; i < bullets.size(); i++)
		bullets[i]->draw(window);
}

void Graphic::showOptions(vector<Option> options, Window& window)
{
	if(options.size() == ZERO)
		return ;
	Point base_point = options[ZERO].getBasePoint();
	drawRing(base_point, SQUARE_LENGTH / TWO, SQUARE_LENGTH + SQUARE_LENGTH / TWO, window);
	for(int i = ZERO; i < options.size(); i++)
		options[i].draw(window);
}

void Graphic::drawRing(Point center, int in_rad, int out_rad, Window& window)
{
	for(int i = -out_rad; i <= out_rad; i++)
	{
		for(int j = -out_rad; j <= out_rad; j++)
		{
			int distance = graphic_tool.getDistance(center, center + Point(i,j));
			if(distance <= out_rad && distance >= in_rad)
			{
				if((i+j) % THREE == ZERO)
					window.draw_point(center + Point(i,j), SILVER);
			}

		}
	}
}

void Graphic::letBegin(Window& window)
{
	window.draw_img(START_IMG);
	window.play_music(START_MUSIC);
	window.show_text(START_MASAGE,START_MASAGE_POINT, BLACK, FONT_PATH, START_MASAGE_SIZE);
	window.update_screen();
	letOut(window);
	window.stop_music();
}