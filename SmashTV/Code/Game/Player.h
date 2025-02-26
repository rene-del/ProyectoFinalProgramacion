#ifndef PLAYER_H
#define PLAYER_H

enum STATES { ST_STILL, ST_MOVING, ST_NOT_ATTACKING, ST_ATTACK };

enum DIRECTION { DIR_RIGHT, DIR_LEFT, DIR_DOWN, DIR_UP };

class Player
{
private:
	int _img;

	int _startX;
	int _startY;

	int _w;
	int _h;
	int _x;
	int _y;

	STATES _actualState;
	DIRECTION _actualDir;

public:
	Charger();
	~Charger();

	void init();
	void update();
	void render();

	STATES getState() { return _actualState; };

	void setImg(int id) { _img = id; };
};

#endif

