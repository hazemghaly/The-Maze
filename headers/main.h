#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define WALL '#'
#define PASSAGE ' '
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FOV_ANGLE (60 * M_PI / 180)
#define NUM_RAYS SCREEN_WIDTH
#define STARTING_SCREEN "./start_screen.bmp"

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gHelloWorld;
extern SDL_Event e;

void generateMaze(int width, int height);
bool init();
bool loadMedia();
void close();

#endif