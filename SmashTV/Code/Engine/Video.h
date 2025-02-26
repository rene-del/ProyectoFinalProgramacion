#ifndef VIDEO_H
#define VIDEO_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#include "SDL.h"

class Video
{
private:
	static Video* _pInstance;

	Video();

public:	
	~Video();

	void renderGraphic(int img, int posXStart, int posYStart, int posX, int posY, int width, int height);
	void clearScreen();
	void updateScreen();
	void close();

	static Video* getInstance();

	SDL_Renderer* _gRenderer;
	SDL_Window* _gWindow;
};

#endif

