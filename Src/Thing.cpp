#include "Thing.hpp"

using namespace std;

Thing::Thing(Point coordinates_, string img_path_)
{
	coordinates = coordinates_;
	img_path = img_path_;
	reverse = false;
}

void Thing::draw(Window& window)
{
	Rectangle dest_rect(coordinates.x - SQUARE_LENGTH / TWO, coordinates.y - SQUARE_LENGTH / TWO,
		SQUARE_LENGTH , SQUARE_LENGTH );
	window.draw_img(img_path, dest_rect, NULL_RECT, ZERO, reverse, false);
}