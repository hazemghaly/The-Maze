#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface *wallSurface;
SDL_Surface *groundSurface;
SDL_Texture *wallTexture;
SDL_Texture *groundTexture;
SDL_Renderer *renderer;
SDL_Window *window;
void texturs(void);
void closewin(void);
SDL_Surface *gHelloWorld = NULL;
/**
 * closewin - main.
*/
void closewin(void)
{
SDL_DestroyTexture(wallTexture);
SDL_DestroyTexture(groundTexture);
wallTexture = NULL;
groundTexture = NULL;
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
}
/**
 * texturs - main.
*/
void texturs(void)
{
wallSurface = IMG_Load("w.jpg");
if (wallSurface == NULL)
	printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
wallTexture = SDL_CreateTextureFromSurface(renderer, wallSurface);
groundSurface = IMG_Load("g.jpg");
if (groundSurface == NULL)
	printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
groundTexture = SDL_CreateTextureFromSurface(renderer, groundSurface);
}
/**
 * main - main.
*/
int main(void)
{
if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1))
{
	printf("Could not initialize SDL: %s.\n", SDL_GetError());
	exit(-1);
}
int imgFlags = IMG_INIT_PNG;
if (!(IMG_Init(imgFlags) & imgFlags))
{
	printf("SDL_image Error: %s\n", IMG_GetError());
	return (1);
}
window = SDL_CreateWindow("Maze",
SDL_WINDOWPOS_UNDEFINED,
SDL_WINDOWPOS_UNDEFINED,
SCREEN_WIDTH, SCREEN_HEIGHT,
SDL_WINDOW_SHOWN);
if (window == NULL)
{
	printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return (1);
}
renderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_ACCELERATED |
											  SDL_RENDERER_PRESENTVSYNC);
if (renderer == NULL)
{
	printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	return (1);
}
texturs();
int quit = 0;
SDL_Event e;
while (!quit)
{
while (SDL_PollEvent(&e) != 0)
{
if (e.type == SDL_QUIT)
{
quit = 1;
}
}
SDL_Rect wallRect = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
SDL_Rect groundRect = {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
SDL_RenderCopy(renderer, groundTexture, NULL, &groundRect);

SDL_RenderPresent(renderer);
}
closewin();/*Cleanup*/
return (0);
}
