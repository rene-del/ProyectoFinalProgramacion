#ifndef VIDEO_H
#define VIDEO_H

#define SCREEN_WIDTH 832
#define SCREEN_HEIGHT 832

#include "SDL.h"

class Video
{
private:
	static Video* _pInstance;

	Video();

public:	
	~Video();

	void renderGraphic(int img, SDL_Rect src, SDL_Rect dst);
	void clearScreen();
	void updateScreen();
	void close();

	static Video* getInstance();

	SDL_Renderer* _gRenderer;
	SDL_Window* _gWindow;
};

#endif

