#ifndef VIDEO_H
#define VIDEO_H

#define SCREEN_WIDTH 832
#define SCREEN_HEIGHT 832

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>


class Video
{
private:
	static Video* _pInstance;

	Video();

public:	
	~Video();

	void renderGraphic(int img, SDL_Rect src, SDL_Rect dst);
	void renderGraphicSmooth(int img, SDL_Rect src, SDL_FRect dst);
	void renderGraphicRotated(int img, SDL_Rect src, SDL_Rect dst, double rotation);
	void clearScreen();
	void updateScreen();
	void close();

	static Video* getInstance();

	TTF_Font* getFont() const { return _font; }

	void renderText(const std::string& text, int x, int y, SDL_Color color, int fontSize = 24);

	SDL_Renderer* _gRenderer;
	SDL_Window* _gWindow;

	TTF_Font* _font; 

};

#endif

