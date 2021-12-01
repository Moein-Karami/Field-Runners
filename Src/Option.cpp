#include "Option.hpp"

using namespace std;

const char EQUAL_KEYS[] = {GATTLING_KEY, MISILE_KEY, TESLA_KEY, GLUE_KEY, UPGRADE_KEY};
const Point POINT_DISTANCES[] = {Point(ZERO, -SQUARE_LENGTH), Point(SQUARE_LENGTH, ZERO),
		Point(ZERO, SQUARE_LENGTH),Point(-SQUARE_LENGTH, ZERO), Point(ZERO, -TWO * SQUARE_LENGTH)};
const string IMAGE_PATH_COLLECTION[] = {GATTLING_IMG, MISILE_IMG, TESLA_IMG, GLUE_IMG, UPGRADE_IMG};

Option::Option(int option_type, Point base_point_)
	:Thing(base_point_ + POINT_DISTANCES[option_type], IMAGE_PATH_COLLECTION[option_type])
{	
	equal_key = EQUAL_KEYS[option_type];
	base_point = base_point_;
	if(option_type == FOUR)
		img_size = 45;
	else
		img_size = SQUARE_LENGTH;
}

Point Option::getBasePoint()
{
	return base_point;
}

char Option::getEqualKey()
{
	return equal_key;
}

void Option::draw(Window& window)
{
	Rectangle dest_rect(coordinates.x - img_size / TWO, coordinates.y - img_size / TWO,
		img_size , img_size );
	window.draw_img(img_path, dest_rect, NULL_RECT, ZERO, reverse, false);
}

Point Option::getCoordinates()
{
	return coordinates;
}