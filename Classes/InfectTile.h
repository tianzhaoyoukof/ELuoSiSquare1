#ifndef __INFECTTILE_H__
#define __INFECTTILE_H__

/*侵染模式的精灵显示，有7种颜色
 * 2015-12-5 创建
 */

#include "cocos2d.h"

USING_NS_CC;

enum InfectTileColor
{
	BLUE_infect = 0,
	GREEN_infect = 1,
	ORANGE_infect = 2,
	PURPLE_infect = 3,
	RED_infect = 4,
	YELLOW_infect = 5,
	BLACK_infect = 6
};

class InfectTile : public Sprite
{
public :
	CREATE_FUNC(InfectTile);
	InfectTile();
	static InfectTile* createTile(int c,int ix,int iy,int bX,int bY,int size);
	bool init();
	/**设置地图块是否被加入队列*/
	void setInQueue(bool b) {m_isInQueue = b;}
	/**得到地图块是否被加入队列*/
	bool getInQueue() const { return m_isInQueue;}

	/**得到颜色*/
	InfectTileColor getTileColor() const {return m_tileColor;}
	/**设置颜色*/
	void setTileColor(InfectTileColor c);

	/**设置延迟计数器*/
	void setDelayCount(int coun) {m_delayCount = coun;}

	/**得到索引*/
	int getIndexX() const {return m_indexX;}
	int getIndexY() const {return m_indexY;}

private:
	/**初始化块*/
	void initTile();
private:
	/**俄罗斯方块地图块的颜色*/
	InfectTileColor m_tileColor;



private:
	/**地图块是否被加入队列*/
	bool m_isInQueue;

	/**延迟计数器*/
	int m_delayCount;

	/**索引*/
	int m_indexX;
	int m_indexY;
};

#endif