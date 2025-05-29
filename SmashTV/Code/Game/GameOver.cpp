#include "GameOver.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"
#include "../Engine/Audio.h"
#include "../Engine/InputManager.h"
#include "SceneDirector.h"
#include "GameState.h"

#include <string>

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;
extern Audio* AUDIO;
extern InputManager* INPUT_MANAGER;
extern SceneDirector* SCENE_DIRECTOR;
extern GameState* GAME_STATE;

GameOver::GameOver()
{
	_channel = 0;
	_music = 0;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.w = 0;
	_dst.y = 0;
	_dst.x = 0;
	_dst.y = 0;

	_nameSet = false;

	_reInit = true;

	_nameBuffer = "";

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		_keyHeld[i] = false;
	}
}

GameOver::~GameOver()
{
}

void GameOver::init()
{
	_music = RESOURCE_MANAGER->loadAndGetAudioID("Assets/Audios/highscore.wav");
	_channel = AUDIO->playAudio(-1, _music, -1);

	_src.x = 0;
	_src.y = 0;
	_src.w = 832;
	_src.h = 832;

	_dst.x = 0;
	_dst.y = 0;
	_dst.w = 832;
	_dst.h = 832;

	_reInit = false;	
	
	SDL_StartTextInput();
}

void GameOver::reinit()
{
	init();
}

void GameOver::update()
{
	for (int i = SDL_SCANCODE_A; i <= SDL_SCANCODE_Z; ++i)
	{
		if (INPUT_MANAGER->getKeyState((SDL_Scancode)i))
		{
			if (!_keyHeld[i] && _nameBuffer.length() < 5)
			{
				_nameBuffer += static_cast<char>('A' + (i - SDL_SCANCODE_A));
				_keyHeld[i] = true;
			}
		}
		else
		{
			_keyHeld[i] = false;
		}
	}

	// BACKSPACE
	if (INPUT_MANAGER->getKeyState(SDL_SCANCODE_BACKSPACE))
	{
		if (!_keyHeld[SDL_SCANCODE_BACKSPACE] && !_nameBuffer.empty())
		{
			_nameBuffer.pop_back();
			_keyHeld[SDL_SCANCODE_BACKSPACE] = true;
		}
	}
	else
	{
		_keyHeld[SDL_SCANCODE_BACKSPACE] = false;
	}

	if (INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN))
	{
		GAME_STATE->setName(_nameBuffer);
		_nameSet = true;
		SDL_StopTextInput();
	}	

	// CONTROL KEY
	bool enter = INPUT_MANAGER->getKeyState(SDL_SCANCODE_RETURN);
	bool highScore = INPUT_MANAGER->getKeyState(SDL_SCANCODE_H);

	// GO MENU
	if (enter)
	{
		_nameSet = false;
		GAME_STATE->setName(_nameBuffer);

		SCENE_DIRECTOR->changeSceneC(SceneEnum::HIGHSCORE, true, _channel);
		SDL_StopTextInput();
	}
}

void GameOver::render()
{
	SDL_Color white = { 255, 255, 255 };
	VIDEO->renderText(_nameBuffer, SCREEN_WIDTH / 2, 700, white);
}
