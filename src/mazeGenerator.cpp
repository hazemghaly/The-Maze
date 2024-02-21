#include "../headers/main.h"
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> getNeighbors(int x, int y) {
    std::vector<std::pair<int, int>> neighbors;

    if (isValidCell(x + 1, y)) neighbors.push_back(std::make_pair(x + 1, y));
    if (isValidCell(x - 1, y)) neighbors.push_back(std::make_pair(x - 1, y));
    if (isValidCell(x, y + 1)) neighbors.push_back(std::make_pair(x, y + 1));
    if (isValidCell(x, y - 1)) neighbors.push_back(std::make_pair(x, y - 1));
    return neighbors;
}

/**
 * generateMaze - Generates a maze based on width and height.
 * @width: the width of the maze.
 * @height: the height of the maze.
 */

void generateMaze(int width, int height)
{
	bool maze[height][width];
	bool visited[height][width];
	std::vector <std::pair<int, int>> neighbours;
	int startX;
	int startY;
	FILE *fp = fopen("maze.txt", "w");

    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
	srand(time(NULL));
	startX = rand() % width;
	startY = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			maze[i][j] = WALL;
		}
	}


    fclose(fp);
}
