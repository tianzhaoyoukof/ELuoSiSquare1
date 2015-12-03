#include "NormalTile.h"

NormalTile* NormalTile::createTile( TileColor c,Vec2 p )
{
	auto tile = NormalTile::create();
	if(tile)
	{
		tile->m_tileColor = c;
		tile->initTile();
		tile->setPosition(p);
		return tile;
	}
	CC_SAFE_DELETE(tile);
	return nullptr;
}

bool NormalTile::init()
{
	if(!Sprite::init())
		return false;
	return true;
}

void NormalTile::initTile()
{
	switch(m_tileColor)
	{
	case BLACK:
		this->initWithFile("NormalMode/black.png");
		break;
	case BLUE:
		this->initWithFile("NormalMode/blue.png");
		break;
	case GREEN:
		this->initWithFile("NormalMode/green.png");
		break;
	case ORANGE:
		this->initWithFile("NormalMode/orange.png");
		break;
	case PURPLE:
		this->initWithFile("NormalMode/purple.png");
		break;
	case RED:
		this->initWithFile("NormalMode/red.png");
		break;
	}
}

void NormalTile::setUNVisiable()
{
	m_isVisible = false;
	this->initWithFile("NormalMode/white.png");
}

void NormalTile::setTileVisible( TileColor c )
{
	m_tileColor = c;
	m_isVisible = true;
	initTile();
}
