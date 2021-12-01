#ifndef _Option_
#define _Option_

#include "LibrariesAndDefines.hpp"
#include "Thing.hpp"

class Option : Thing
{
	private :
		char equal_key;
		Point base_point;
		int img_size;
	public :
		Option(int option_type, Point base_point_);
		Point getBasePoint();
		char getEqualKey();
		void draw(Window& window);
		Point getCoordinates();
};


#endif