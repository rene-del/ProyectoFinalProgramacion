#include "Enemy.h"

Enemy::Enemy()
{
	_isDead = false;
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
}

void Enemy::update(Player* player)
{
}

void Enemy::render()
{
}

bool Enemy::checkCollision(SDL_Rect)
{
	return false;
}
