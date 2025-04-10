#ifndef VIDEO_H
#define VIDEO_H

#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 840

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

