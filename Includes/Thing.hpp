#ifndef _Thing_
#define _Thing_

#include "LibrariesAndDefines.hpp"

class Thing
{
	protected :
		Point coordinates;
		std::string img_path;
		bool reverse;
	public :
		Thing(Point coordinates_, std::string img_path_=BLANK);
		virtual void draw(Window& window);
};

#endif