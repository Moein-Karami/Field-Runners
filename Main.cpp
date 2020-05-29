#include "LibrariesAndDefines.hpp"
#include "Game.hpp"
#include "Tool.hpp"
using namespace std;

int main()
{
	Tool main_tool;
	vector<vector<int>> data = main_tool.getInput();
	Game game(data);
	game.play(data);
}
	