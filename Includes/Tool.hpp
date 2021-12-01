#ifndef _Tool_
#define _Tool_

#include "LibrariesAndDefines.hpp"

class Tool 
{
	public :
		std::vector<std::vector<int>> getInput();
		std::vector<int> convertStringToVectorOfInt(std::string input, char divider);
		std::vector<std::string> divideStringByChar(std::string str, char divider);
		std::vector<int> convertStringsToInts(std::vector<std::string> input);
		Point getCenterOfSquare(Point squre_coordinates);
		std::vector<Point> buildPixelPath(std::vector<int> input_path);
		std::vector<Point> makePairVectorData(std::vector<int> input);
		std::vector<Point> connectTwoSquare(Point square1, Point square2);
		Point fixChosenPoint(Point chosen_point);
		bool isChosenPointInMap(Point chosen_point);
		int getDistance(Point point1, Point point2);
		Point moveToDestination(Point start, Point finish, int speed);
		bool checkEqualityOfPoints(Point point1, Point point2);
		std::vector<Point> completePath(std::vector<Point> path);
};

#endif