#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "Scene.h"

class Menu : public Scene
{
public:
	Menu();
	~Menu() override;

	void init() override;
	void reinit() override;
	void update() override;
	void render() override;

private:
	int _texId;

	SDL_Rect _src;
	SDL_Rect _dst;
};

#endif

