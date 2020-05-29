#include "Tool.hpp"

using namespace std;

vector<vector<int>> Tool :: getInput()
{
	vector<vector<int>> input;
	string line;
	while(getline(cin, line))
	{
		input.push_back(convertStringToVectorOfInt(line, SPACE));
	}
	return input;
}

vector<int> Tool :: convertStringToVectorOfInt(string input, char divider)
{
	vector<string> divided_input = divideStringByChar(input, divider);
	vector<int> output = convertStringsToInts(divided_input);
	return output;
}

vector<string> Tool :: divideStringByChar(string str, char divider)
{
	vector<string> divided_str;
	str += divider;
	for(int i=ZERO; i < str.size(); i++)
	{
		string word;
		while(str[i] != divider)
		{
			word += str[i];
			i++;
		}
		if(word.size())
			divided_str.push_back(word);
	}
	return divided_str ;
}

vector<int> Tool :: convertStringsToInts(vector<string> input)
{
	vector<int> output;
	for(int i = ZERO; i < input.size(); i++)
		output.push_back(stoi(input[i]));
	return output;
}

Point Tool::getCenterOfSquare(Point square_coordinates)
{
	return Point(TOP_LEFT_X + square_coordinates.x * SQUARE_LENGTH + SQUARE_LENGTH /TWO,
		TOP_LEFT_Y + square_coordinates.y * SQUARE_LENGTH + SQUARE_LENGTH /TWO);
}

vector<Point> Tool::buildPixelPath(vector<int> input_path)
{
	vector<Point> pair_input_path=makePairVectorData(input_path);
	vector<Point> path;
	for(int i = ZERO; i < pair_input_path.size() - ONE; i++)
	{
		vector<Point> tmp = connectTwoSquare(pair_input_path[i], pair_input_path[i + 1]);
		for(int j = ZERO; j < tmp.size(); j++)
			path.push_back(tmp[j]);
	}
	return path;
}

vector<Point> Tool::makePairVectorData(vector<int> input)
{
	vector<Point> output;
	for(int i = ZERO; i < input.size(); i += TWO)
		output.push_back(Point(input[i], input[i+ONE]));
	return output;
}

vector<Point> Tool::connectTwoSquare(Point square1, Point square2)
{
	vector<Point> path;
	Point square1_center = getCenterOfSquare(square1);
	Point square2_center = getCenterOfSquare(square2);
	while(checkEqualityOfPoints(square1_center, square2_center) == false)
	{
		path.push_back(square1_center);
		if(square1_center.x != square2_center.x)
			square1_center.x += ONE + TWO * -(int)(square2_center.x < square1_center.x);
		else
			square1_center.y += ONE + TWO * -(int)(square2_center.y < square1_center.y);
	}
	path.push_back(square1_center);;
	return path;
}

Point Tool::fixChosenPoint(Point chosen_point)
{
	if(isChosenPointInMap(chosen_point) == false)
	{
		chosen_point = OUT_POINT;
		return chosen_point;
	}
	Point chosen_square = Point((chosen_point.x - TOP_LEFT_X) / SQUARE_LENGTH,
		(chosen_point.y - TOP_LEFT_Y) / SQUARE_LENGTH);
	chosen_point = getCenterOfSquare(chosen_square);
	return chosen_point;
}

bool Tool::isChosenPointInMap(Point chosen_point)
{
	if(chosen_point.x < TOP_LEFT_X || chosen_point.x > TOP_LEFT_X + 
		MAP_WIDTH_SQUARES * SQUARE_LENGTH)
		return false;
	if(chosen_point.y < TOP_LEFT_Y || chosen_point.y > TOP_LEFT_Y + 
		MAP_HEIGHT_SQUARES * SQUARE_LENGTH)
		return false;
	return true;
}

int Tool::getDistance(Point point1, Point point2)
{
	int x_distance=point1.x - point2.x;
	int y_distance=point1.y - point2.y;
	return sqrt(x_distance*x_distance+y_distance*y_distance);
}

Point Tool::moveToDestination(Point start, Point finish, int speed)
{
	if(getDistance(start, finish) <=speed)
		return finish;
	double angle=atan2(finish.y - start.y, finish.x - start.x);
	int new_y = start.y + (double)speed * sin(angle);
	int new_x = start.x + (double)speed * cos(angle);
	return Point(new_x,new_y);
}

bool Tool::checkEqualityOfPoints(Point point1, Point point2)
{
	return (point1.x == point2.x && point1.y == point2.y);
}


vector<Point> Tool::completePath(vector<Point> path)
{
	vector<Point> complete_path;
	for(int i=ZERO; i< path.size() - ONE; i++)
	{
		complete_path.push_back(path[i]);
		while(complete_path.back().x < path[i + ONE].x)
			complete_path.push_back(Point(complete_path.back().x + 1, complete_path.back().y));
		while(complete_path.back().x > path[i + ONE].x)
			complete_path.push_back(Point(complete_path.back().x - 1, complete_path.back().y));
		while(complete_path.back().y < path[i + ONE].y)
			complete_path.push_back(Point(complete_path.back().x, complete_path.back().y + 1));
		while(complete_path.back().y > path[i + ONE].y)
			complete_path.push_back(Point(complete_path.back().x, complete_path.back().y - 1));

	}
	complete_path.push_back(path.back());
	return complete_path;
}