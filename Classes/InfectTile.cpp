#include "InfectTile.h"

InfectTile::InfectTile():
	m_tileColor(BLUE_infect),
	m_isInQueue(false),
	m_delayCount(0)
{

}

InfectTile* InfectTile::createTile( int c,int ix,int iy,int bX,int bY,int size )
{
	auto tile = InfectTile::create();
	if(tile)
	{
		tile->m_tileColor = (InfectTileColor)c;
		tile->initTile();
		tile->m_indexX = ix;
		tile->m_indexY = iy;
		tile->setPosition(Vec2(bX + ix * size,bY + iy * size));
		return tile;
	}
	CC_SAFE_DELETE(tile);
	return nullptr;
}

bool InfectTile::init()
{
	if(!Sprite::init())
		return false;
	return true;
}

void InfectTile::initTile()
{
	switch(m_tileColor)
	{
	case BLUE_infect:
		this->initWithFile("InfectMode/blue.png");
		break;
	case GREEN_infect:
		this->initWithFile("InfectMode/green.png");
		break;
	case ORANGE_infect:
		this->initWithFile("InfectMode/orange.png");
		break;
	case PURPLE_infect:
		this->initWithFile("InfectMode/purple.png");
		break;
	case RED_infect:
		this->initWithFile("InfectMode/red.png");
		break;
	case YELLOW_infect:
		this->initWithFile("InfectMode/yellow.png");
		break;
	}
}

void InfectTile::setTileColor( InfectTileColor c )
{
	m_tileColor = c;
	auto lambda = CallFunc::create([&](){this->initTile();});
	this->stopAllActions();
	this->runAction(Sequence::create(DelayTime::create(m_delayCount * 0.04),lambda,NULL));
}