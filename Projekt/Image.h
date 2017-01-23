#pragma once
#include "SDL.h"
#include <iostream>
#include <string>

class Image
{
	SDL_Surface *image;
	SDL_Window *window;
	SDL_Surface *screenSurface;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

public:

	void createWindow();
	SDL_Surface *displayBitMap(char*);
	SDL_Surface *loadBitMap(char *);
	SDL_Color getPixel(int, int);
	bool isMessageFittedIn(int, char *);
	bool isBmpRightSize(char*);
	void saveBMP(SDL_Surface *, char *);
	void setPixel(int, int, Uint8, Uint8, Uint8);
	Image();
	~Image();

};