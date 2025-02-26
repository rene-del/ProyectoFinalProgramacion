#include "Player.h"
#include "Video.h"
#include "InputManager.h"
#include "TimeManager.h"

extern Video* VIDEO;
extern InputManager* INPUT_MANAGER;
extern TimeManager* TIME_MANAGER;

Charger::Charger()
{
}

Charger::~Charger()
{
}

void Charger::init()
{
	_img = 0;

	_startX = 0;
	_startY = 0;

	_w = 96;
	_h = 96;
	_x = (SCREEN_WIDTH / 2) - (_w / 2);
	_y = (SCREEN_HEIGHT / 2) - (_h / 2);

	_actualState = ST_STILL;
	_actualDir = DIR_DOWN;
}

void Charger::update()
{
	
}

void Charger::render()
{
	VIDEO->renderGraphic(_img, _startX, _startY, _x, _y, _w, _h);
}
