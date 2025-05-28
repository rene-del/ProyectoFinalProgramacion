#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include "Scene.h"
#include <string>

class GameOver : public Scene
{
public:
	GameOver();
	~GameOver() override;

	void init() override;
	void reinit() override;
	void update() override;
	void render() override;

private:
	int _texId;

	bool _nameSet;

	bool _keyHeld[SDL_NUM_SCANCODES];


	std::string _nameBuffer;


	SDL_Rect _src;
	SDL_Rect _dst;
};

#endif

