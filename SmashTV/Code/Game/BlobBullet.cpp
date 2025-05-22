#include "BlobBullet.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Video.h"

extern ResourceManager* RESOURCE_MANAGER;
extern Video* VIDEO;

BlobBullet::BlobBullet()
{
	_img = 0;
	_limit = 0;

	_src.x = 0;
	_src.y = 0;
	_src.w = 0;
	_src.h = 0;

	_dst.x = 0;
	_dst.y = 0;
	_dst.w = 0;
	_dst.h = 0;
}

BlobBullet::~BlobBullet()
{
}

void BlobBullet::init(int x, int y, int w, int h)
{
	_img = RESOURCE_MANAGER->loadAndGetGraphicID("Assets/Enemies/Blob_Shot.png");

	_src.x = 0;
	_src.y = 0;
	_src.w = 16;
	_src.h = 11;

	_dst.x = x - 10 + (w / 2 - _src.w / 2);
	_dst.y = y + (h / 2 - _src.h / 2);
	_dst.w = 16;
	_dst.h = 11;
}

void BlobBullet::update()
{
	_dst.x -= 2;
	_limit++;
}

void BlobBullet::render()
{
	VIDEO->renderGraphic(_img, _src, _dst);
}
